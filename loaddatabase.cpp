#include "loaddatabase.h"
#include <fstream>
void ReadImageMatchPair(const string & strDatabasePath, vector<std::pair<size_t, size_t>>& vecImagePair)
{
		//测试部分
		Database   currenDatabase(strDatabasePath);
		DatabaseTransaction dTran(&currenDatabase);
		int nC=currenDatabase.NumCameras();
		int nI=currenDatabase.NumImages();
		int nK=currenDatabase.NumKeypoints();
		int nNK=currenDatabase.MaxNumKeypoints();
		int nD=currenDatabase.NumDescriptors();
		int nND=currenDatabase.MaxNumDescriptors();
		int nNM=currenDatabase.NumMatches();
		int nNMIP=currenDatabase.NumMatchedImagePairs();
		int nVP=currenDatabase.NumVerifiedImagePairs();
		//读取数据部分
		vector<size_t>  vecImagePairId;
		
		vector<TwoViewGeometry> vecTwoViewGeometry;
		currenDatabase.ReadTwoViewGeometries(&vecImagePairId, &vecTwoViewGeometry);
		PairIdToImageId(vecImagePairId, vecImagePair);
	

		

}

void PairIdToImageId(const vector<size_t>& vecPairId, vector<std::pair<size_t, size_t>>& vecImageId)
{
	size_t   kMaxNumImages =
		static_cast<size_t>(std::numeric_limits<int32_t>::max());
	for (auto pairId : vecPairId)
	{
		size_t image_id2, image_id1;
		image_id2 = static_cast<image_t>(pairId % kMaxNumImages);
		image_id1 = static_cast<image_t>((pairId - image_id2) / kMaxNumImages);
		vecImageId.push_back(std::pair<size_t, size_t>(image_id1, image_id2));
	}
}

void WriteImagePairToFile(const vector<std::pair<size_t, size_t>>& vecImagePair, const string & strPath)
{
	ofstream outFile;
	outFile.open(strPath.c_str(), ios::out);
	for (auto &imp:vecImagePair)
	{
		outFile << imp.first << "," << imp.second << endl;
	}
	outFile.close();

}

void ReadDescriptor(const string &dataPath, vector<FeatureDescriptors> & vecFeature, map<int, int> & mapImageRowNum)
{
	Database database(dataPath);
	DatabaseTransaction database_transaction(&database);

	const std::vector<Image> images = database.ReadAllImages();

	FeatureDescriptors descriptors;

	std::vector<size_t> image_idxs;
	size_t num_descriptors = 0;

	// All images in the database.
	image_idxs.resize(images.size());
	std::iota(image_idxs.begin(), image_idxs.end(), 0);
	num_descriptors = database.NumDescriptors();
	


	

	descriptors.resize(num_descriptors, 128);
	std::vector<std::string>  vecImagename;
	size_t descriptor_row = 0;
	for (const auto image_idx : image_idxs) {
		const auto& image = images.at(image_idx);
		string str = image.Name();
		vecImagename.push_back(str);
		const FeatureDescriptors image_descriptors =
			database.ReadDescriptors(image.ImageId());
		int  nRow = image_descriptors.rows();
		descriptors.block(descriptor_row, 0, image_descriptors.rows(), 128) =
			image_descriptors;
		mapImageRowNum.insert(pair<int, int>(image_idx, image_descriptors.rows()));
		descriptor_row += image_descriptors.rows();
	}
	
	vecFeature.push_back(descriptors);

	
}
void ReadMatchMatrix(const string &dataPath,const string &strOutfile)
{
	Database database(dataPath);
	if (database.NumImages() == 0) {
		return;
	}
	ofstream fileout;
	fileout.open(strOutfile.c_str(), std::ios::out);
	// Sort the images according to their name.
	std::vector<Image> images = database.ReadAllImages();
	std::sort(images.begin(), images.end(),
		[](const Image& image1, const Image& image2) {
			return image1.Name() < image2.Name();
		});
	// Map image identifiers to match matrix locations.
	std::unordered_map<image_t, size_t> image_id_to_idx;
	for (size_t idx = 0; idx < images.size(); ++idx) {
		image_id_to_idx.emplace(images[idx].ImageId(), idx);
	}
	double ** storeScore = new double *[images.size()];
	for (int i=0;i<images.size();++i)
	{
		storeScore[i] = new double[images.size()];
		for (int j = 0; j < images.size(); ++j)
			storeScore[i][j] = 0;
	}
	std::vector<std::pair<image_t, image_t>> image_pairs;
	std::vector<int> num_inliers;
	database.ReadTwoViewGeometryNumInliers(&image_pairs, &num_inliers);

	// Fill the match matrix.
	if (!num_inliers.empty()) {
		const double max_value =
			std::log1p(*std::max_element(num_inliers.begin(), num_inliers.end()));
		for (size_t i = 0; i < image_pairs.size(); ++i) {
			const double value = std::log1p(num_inliers[i]) / max_value;
			const size_t idx1 = image_id_to_idx.at(image_pairs[i].first);
			const size_t idx2 = image_id_to_idx.at(image_pairs[i].second);
			storeScore[idx1][idx2] = value;
			storeScore[idx2][idx1] = value;
		}
	}
	for (int i=0;i<images.size();++i)
	{
		for (int j=0;j<images.size();++j)
		{
			fileout << storeScore[i][j] << ",";
		}
		fileout << endl;
	}
	fileout.close();
}

void WriteDescriptorToFile(const string strPath, const vector<FeatureDescriptors>& vecFeature, const map<int, int>& mapImageRowNum)
{
	//FILE * OutFile=fopen(strPath.c_str(),"wb");
	ofstream OutFile;
	OutFile.open(strPath.c_str(), std::ios::out | std::ios::binary);
	//TODO：将特征描述符按图像写入文件
	//OutFile << "File discirption, image index, descriptor"<<endl;
	auto veFeatures = vecFeature[0];
	int nRow = veFeatures.rows();
	int nCol = veFeatures.cols();
	//写入文件行列数
	OutFile.write((char*)&nRow, sizeof(nRow));
	OutFile.write((char*)&nCol, sizeof(nCol));
	int  outIndex = 0;
	for (auto idx:mapImageRowNum)
	{
		int nIndex = idx.first;
		int nFeatureNum = idx.second;
		for (int i=0;i<nFeatureNum;++i)
		{
			OutFile.write((char*)&nIndex, sizeof(nIndex));

			for (int j=0;j<128;++j)
			{
				float temp = (float(veFeatures(outIndex, j)));
				OutFile.write((char *)&temp,sizeof(temp));
				
			}
			outIndex++;
		}
	}
	OutFile.good();
	OutFile.close();
}

void WriteDescriptorToOpenCV(const string strPath, const vector<FeatureDescriptors>& vecFeature, const map<int, int>& mapImageRowNum)
{
	//FILE * OutFile=fopen(strPath.c_str(),"wb");
	ofstream OutFile;
	OutFile.open(strPath.c_str(), std::ios::out);
	//TODO：将特征描述符按图像写入文件
	//OutFile << "File discirption, image index, descriptor"<<endl;
	auto veFeatures = vecFeature[0];
	int nRow = veFeatures.rows();
	int nCol = veFeatures.cols();
	//写入文件行列数
// 	OutFile.write((char*)&nRow, sizeof(nRow));
// 	OutFile.write((char*)&nCol, sizeof(nCol));
	int  outIndex = 0;
	for (auto idx : mapImageRowNum)
	{
		int nIndex = idx.first;
		int nFeatureNum = idx.second;
		for (int i = 0; i < nFeatureNum; ++i)
		{
			char cLabel = NumberToChar(nIndex);
			OutFile<<cLabel<<",";

			for (int j = 0; j < 128; ++j)
				OutFile << float(veFeatures(outIndex, j)) << ",";
			OutFile << endl;
			outIndex++;
		}
	}

	OutFile.close();



}

char NumberToChar(int nInput)
{
	int nA = 'A';
	char cReturn = 'A' + nInput;
	return cReturn;

}
