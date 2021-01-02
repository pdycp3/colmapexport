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
//�����ݿ����ƥ���ƥ���Ӱ������id
void ReadImageMatchPair(const string & strDatabasePath, vector<std::pair<size_t, size_t>>& vecImagePair);
//����idת����Ӱ�����id
void PairIdToImageId(const vector<size_t> & vecPairId, vector<std::pair<size_t, size_t>> & vecImageId);
//TODO:ȱ��Ӱ������id��ͼ�����ƶ�Ӧ��ת������
//��Ӱ�������idд���ļ��Թ���ͼ
void WriteImagePairToFile(const vector<std::pair<size_t,size_t>> & vecImagePair,const string & strPath);
//�����ݿ����Ӱ���������������
void ReadDescriptor(const string &dataPath,vector<FeatureDescriptors> & vecFeature,map<int,int> & mapImageRowNum);
//������������д���ļ�
void WriteDescriptorToFile(const string strPath,const vector<FeatureDescriptors> &vecFeature, const map<int,int> & mapImageRowNum);
//д��opencv�ļ�
void WriteDescriptorToOpenCV(const string strPath, const vector<FeatureDescriptors> &vecFeature, const map<int, int> & mapImageRowNum);
void ReadMatchMatrix(const string &dataPath, const string &strOutfile);
//imag
char NumberToChar(int nInput);







#endif//
