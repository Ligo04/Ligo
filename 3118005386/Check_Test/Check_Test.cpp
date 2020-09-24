#include "pch.h"
#include "CppUnitTest.h"
#include "../DuplicateChecking/Simhasher.h"
const char* const DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";
const char* const IDF_PATH = "dict/idf.utf8";
const char* const STOP_WORD_PATH = "dict/stop_words.utf8";
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CheckTest
{
	TEST_CLASS(CheckTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//文件打不开
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "123.txt";
			std::string str2 = "456.txt";
			std::string str3 = "ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsFalse(sim.Parse(names));
		}

		TEST_METHOD(TestMethod2)
		{
			//相似
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig.txt";
			std::string str2 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig_0.8_add.txt";
			std::string str3 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsTrue(sim.Parse(names));
			sim.isSimilarity(50);
		}

		TEST_METHOD(TestMethod3)
		{
			//不相似
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig.txt";
			std::string str2 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig_0.8_dis_15.txt";
			std::string str3 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsTrue(sim.Parse(names));
			sim.isSimilarity(50);
		}
		TEST_METHOD(TestMethod4)
		{
			//其他几个文件与原文件对比
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig.txt";
			std::string str2 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig_0.8_dis_1.txt";
			std::string str3 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsTrue(sim.Parse(names));
			sim.isSimilarity(50);
		}
		TEST_METHOD(TestMethod5)
		{
			//其他几个文件与原文件对比
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig.txt";
			std::string str2 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig_0.8_dis_10.txt";
			std::string str3 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsTrue(sim.Parse(names));
			sim.isSimilarity(50);
		}
		TEST_METHOD(TestMethod6)
		{
			//其他几个文件与原文件对比
			Simhasher sim(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
			std::vector<std::string> names;
			std::string str1 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig.txt";
			std::string str2 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\test\\orig_0.8_dis_15.txt";
			std::string str3 = "D:\\Github\\SoftwareEngineering\\3118005386\\DuplicateChecking\\ans.txt";
			names.push_back(str1);
			names.push_back(str1);
			names.push_back(str1);
			Assert::IsTrue(sim.Parse(names));
			sim.isSimilarity(50);
		}
	};
}
