#include "feature/sift.h"
#include "loaddatabase.h"
#include "sqlite3.h"
#include <iostream>
#include <vector>
using namespace std;
//����Ŀ��Ŀ�����ڲ���Ӱ������ĵĲ�������;
//TODO:
//��һ��������ȡ��
//������ȡ���ִ˲�����openmvg��ʵ�ֺ�Ǩ�ƹ���;
//ֱ����colmap����İ�
//�ڶ��������������ݿ⼴�ʻ���
//���ɭ��ʵ��
//�ʻ�������;
//��ȡ���ݿ�;
//����������������ʽ�����Ӱ����ڽӹ�ϵ;
//�����ݿ��ȡ������
//��׼��
void LoadImageDescriptor(const string &strDataBasePath,vector<int> & vecDescrrptor)
{






}
int main()
{
	string  strPath = "D:\\data\\colmatest\\coltest.db";
	string strpath1 = "D:\\data\\colmatest\\modelste.db";
	string strpath2 = "D:\\data\\colmatest\\features.data";
	string strpath3 = "G:\\data\\smalltest\\smal.db";
	string strpath4 = "G:\\data\\arialimage20\\uav20.db";
	string strpath5 = "G:\\data\\uavtest\\uavexhaust.db";
	string strpath6 = "G:\\data\\south-building\\database.db";
	string strpath7 = "D:\\3DOpenSource\\Cameratest\\camertest.db";
	string strpath8 = "G:\\data\\unorderedtest\\1\\1.db";
	string strpathbinary= "D:\\data\\colmatest\\coltest.ibx";
	string strUavPath = "E:\\data\\uav\\1\\100.db";
	string strUavPathbinary= "E:\\data\\uav\\1\\featuresUAV.ibx";
	string strpathbinary4 = "G:\\data\\arialimage20\\uav20.ibx";
	string strpathbinary5= "G:\\data\\uavtest\\uavexhaust.ibx";
	string strpathbinary6= "G:\\data\\south-building\\southbuilding.ibx";
	string strpathbinary7 = "D:\\3DOpenSource\\Cameratest\\camertest.ibx";
	string strpathbinary8 = "G:\\data\\unorderedtest\\1\\1.ibx";

	string strOpencvDescriptor = "G:\\data\\arialimage20\\uav20opencv.txt";
	string strHeatmap = "G:\\data\\arialimage20\\uav20Heatmap.txt";
	vector<FeatureDescriptors>  vecFeature;
	map<int, int> mapImageNumber;
	ReadDescriptor(strpath8, vecFeature,mapImageNumber);
	//vector<std::pair<size_t, size_t>> vecImagePair;
	//ReadImageMatchPair(strPath, vecImagePair);
	//string strOutFile = "D:\\data\\colmatest\\match.txt";
	//WriteImagePairToFile(vecImagePair,strOutFile);
	WriteDescriptorToFile(strpathbinary8,vecFeature,mapImageNumber);
	//WriteDescriptorToOpenCV(strOpencvDescriptor, vecFeature, mapImageNumber);
	//ReadMatchMatrix(strpath4,strHeatmap);
	cout << "test" << endl;
	system("pause");
	return 0;




}


