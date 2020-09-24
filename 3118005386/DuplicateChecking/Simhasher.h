#pragma once
#include<functional>
#include<math.h>
#include<algorithm>
#include<string>
#include<utility>
#include<vector>
#include<bitset>
#include<fstream>
#include<sstream>
#include<iostream>
#include<Windows.h>
#include "cppjieba/Jieba.hpp"



std::string string_To_UTF8(const std::string& str);
std::string UtfToGbk(const char* utf8);
uint64_t binaryStringToUint64(const std::string& bin);


class Simhasher
{

public:
	Simhasher(const char* _DICT_PATH,
		const char*  _HMM_PATH,
		const char*  _USER_DICT_PATH,
		const char*  _IDF_PATH,
		const char*  _STOP_WORD_PATH);
	~Simhasher();

public:
	// ����,�����ı����� [ԭ���ļ�] [��Ϯ�����ĵ��ļ�] [���ļ�]
	bool Parse(int argc,char** argv);

	// �ж��Ƿ����������ı��Ƿ�����(Ĭ�Ϻ���������ֵΪ3)
	void isSimilarity(uint32_t topk ,unsigned int n = 3);

private:


	//�ִʵõ�hashֵ��Ȩֵ(Ĭ��ȡȨ�ص�ǰ100��)
	std::vector<std::pair<uint64_t, int>> Participle(std::string context, uint32_t topk = 100);
	//�������µ�simhashֵ
	uint64_t CalculaterSimhash(std::vector<std::pair<uint64_t, int>> fw);
	//����������ֵΪ3
	std::pair<bool, double> CalcularSimilarity(uint64_t lhs, uint64_t rhs, unsigned short n);
private:									
	cppjieba::Jieba																mJieba;					//�����
	std::vector<std::pair<std::string,std::string>>								mFiles;					//�ļ�������������

	std::ofstream                                                               mLog;					//�����־
};
