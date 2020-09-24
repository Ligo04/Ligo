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
	// 分析,加载文本内容 [原文文件] [抄袭版论文的文件] [答案文件]
	bool Parse(int argc,char** argv);

	// 判断是否相似两个文本是否相似(默认海明距离阈值为3)
	void isSimilarity(uint32_t topk ,unsigned int n = 3);

private:


	//分词得到hash值与权值(默认取权重的前100个)
	std::vector<std::pair<uint64_t, int>> Participle(std::string context, uint32_t topk = 100);
	//计算文章的simhash值
	uint64_t CalculaterSimhash(std::vector<std::pair<uint64_t, int>> fw);
	//海明距离阈值为3
	std::pair<bool, double> CalcularSimilarity(uint64_t lhs, uint64_t rhs, unsigned short n);
private:									
	cppjieba::Jieba																mJieba;					//结巴类
	std::vector<std::pair<std::string,std::string>>								mFiles;					//文件中名字与内容

	std::ofstream                                                               mLog;					//输出日志
};
