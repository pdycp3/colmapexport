#pragma once
#ifndef LOAD_DATABASE_H
#define LOAD_DATABASE_H


#include "base/database.h"

#include "feature/utils.h"
#include <string>
#include <numeric>
#include <map>
typedef Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> FeatureDescriptors;
using namespace colmap;
using namespace std;
//从数据库读出匹配的匹配的影像索引id
void ReadImageMatchPair(const string & strDatabasePath, vector<std::pair<size_t, size_t>>& vecImagePair);
//索引id转换成影像本身的id
void PairIdToImageId(const vector<size_t> & vecPairId, vector<std::pair<size_t, size_t>> & vecImageId);
//TODO:缺少影像索引id与图像名称对应的转换函数
//将影像的索引id写入文件以供作图
void WriteImagePairToFile(const vector<std::pair<size_t,size_t>> & vecImagePair,const string & strPath);
//从数据库读出影像特征点的描述符
void ReadDescriptor(const string &dataPath,vector<FeatureDescriptors> & vecFeature,map<int,int> & mapImageRowNum);
//将特征描述符写入文件
void WriteDescriptorToFile(const string strPath,const vector<FeatureDescriptors> &vecFeature, const map<int,int> & mapImageRowNum);
//写入opencv文件
void WriteDescriptorToOpenCV(const string strPath, const vector<FeatureDescriptors> &vecFeature, const map<int, int> & mapImageRowNum);
void ReadMatchMatrix(const string &dataPath, const string &strOutfile);
//imag
char NumberToChar(int nInput);







#endif//
