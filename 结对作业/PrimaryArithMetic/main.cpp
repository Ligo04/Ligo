#include<iostream>
#include <ctime>
#include<regex>
#include"PriAriCreator.h"

#pragma warning(disable:26451)

const std::string helpContext = "help:\n"
"-n [number] -r [natural] [frac] [down]               生成相应数量的题目与答案\n (分别对应自然数、真分数和真分数分母的范围)"
"-e [title] -a [answer]     分别对应题目文件路径与答案文件路径\n";

const std::string error = "参数错误 请输入help来查看参数\n";


bool IsALLNum(std::string str)
{
	std::regex dd("[0-9]*");
	std::smatch sm;
	return  std::regex_match(str, sm, dd);
}

void Parse(int argc, char** argv)
{
	if (argc == 2)
	{
		if (std::string(argv[1])._Equal("help"))
		{
			std::cout << helpContext;
		}
		else
		{
			std::cout << error;
		}
	}
	else if (argc == 3)
	{
		if (std::string(argv[1])._Equal("-n")&& IsALLNum(argv[2]))
		{
			std::clock_t c_start = std::clock();
			int numTitile = std::stoi(argv[2]);
			PriAriCreator* Par=new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(numTitile);
			delete Par;
			std::clock_t c_end = std::clock();
			std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
		}
		else
		{
			std::cout << error;
		}
	}
	else if (argc == 5)
	{
		if (std::string(argv[1])._Equal("-e") && std::string(argv[3])._Equal("-a"))
		{
			std::clock_t c_start = std::clock();
			PriAriCreator* Par = new PriAriCreator();
			if (Par->ReadTitilesAndAnswer(std::string(argv[2]), std::string(argv[4])))
			{
				Par->VerificationAnswer();
			}
			delete Par;
			std::clock_t c_end = std::clock();
			std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
		}
		else if (std::string(argv[1])._Equal("-n") && std::string(argv[3])._Equal("-r")
				&& IsALLNum(argv[2])&& IsALLNum(argv[4]))
		{
			std::clock_t c_start = std::clock();
			int numTitile = std::stoi(argv[2]);
			long long numNatural = std::stoll(argv[4]);
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(numTitile, numNatural);
			std::clock_t c_end = std::clock();
			std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
		}
		else
		{
			std::cout << error;
		}
	}
	else if (argc == 6)
	{
		if (std::string(argv[1])._Equal("-n") && std::string(argv[3])._Equal("-r")
			&& IsALLNum(argv[2])&& IsALLNum(argv[4])&& IsALLNum(argv[5]))
		{
			std::clock_t c_start = std::clock();
			int numTitile = std::stoi(argv[2]);
			long long numNatural = std::stoll(argv[4]);
			long long numFrac= std::stoll(argv[5]);
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(numTitile, numNatural, numFrac);
			std::clock_t c_end = std::clock();
			std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
		}
		else
		{
			std::cout << error;
		}
	}
	else if (argc == 7)
	{
		if (std::string(argv[1])._Equal("-n") && std::string(argv[3])._Equal("-r")
			&& IsALLNum(argv[2])&& IsALLNum(argv[4])&& IsALLNum(argv[5])&& IsALLNum(argv[6]))
		{
			std::clock_t c_start = std::clock();
			int numTitile = std::stoi(argv[2]);
			long long numNatural = std::stoll(argv[4]);
			long long numFrac = std::stoll(argv[5]);
			long long numDown= std::stoll(argv[6]);
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(numTitile, numNatural, numFrac, numDown);
			std::clock_t c_end = std::clock();
			std::cout << "总耗时:" << static_cast<double>(c_end - c_start) / 1000 << "s" << std::endl;
		}
		else
		{
			std::cout << error;
		}
	}
}

int main(int argc, char** argv)
{
	Parse(argc, argv);
	return 0;
}