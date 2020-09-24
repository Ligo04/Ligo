#include"Simhasher.h"
#include<time.h>
#include<iostream>
const char* const DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";
const char* const IDF_PATH = "dict/idf.utf8";
const char* const STOP_WORD_PATH = "dict/stop_words.utf8";

int test()
{

};

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		std::cout << "输入参数过少\n";
		return 0;
	}

	std::clock_t c_start = std::clock();												//开始计时

	std::vector<std::string> names;
	for (int i = 1; i < argc; ++i)
	{
		names.push_back(argv[i]);
	}

	Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	if (sim.Parse(names))
	{
		sim.isSimilarity(50);
	}
	std::clock_t c_end = std::clock();
	std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
	return 0;
}
