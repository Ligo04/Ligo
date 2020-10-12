#include "PriAriCreator.h"
#include<iostream>

PriAriCreator::PriAriCreator()
	:mDre(static_cast<unsigned int>(time(nullptr))),
	mCalculator(),
	mInfixs(),
	mAnswers()
{

}

PriAriCreator::~PriAriCreator()
{
	if (mTitleFile.is_open())
	{
		mTitleFile.close();
	}
	if (mAnswerFile.is_open())
	{
		mAnswerFile.close();
	}
}

void PriAriCreator::CreateAriTitlesAndAnswer(int titleNums, long long naturlrange, long long fracrange, long long downrange)
{
	for (int i = 0; i < titleNums;)
	{
		int opNum = random_Int(1, mOpNumMax);
		std::vector<Frac> numbers;
		for (int i = 0; i <= opNum; ++i)
		{
			//产生随机数(整数还是分数)
			int isCreate = random_Int(0, 1);
			if (isCreate == 0)
			{
				long long num_R = random_LL(1, naturlrange);
				Frac frac(num_R, 1);
				numbers.push_back(frac);
			}
			else if (isCreate == 1)
			{
				long long num_2 = random_LL(1, downrange);
				long long num_1 = random_LL(1, fracrange * num_2);
				Frac frac(num_1, num_2);
				numbers.push_back(frac);
			}
		}
		std::vector<std::string> ops;
		//随机生成符号
		for (int i = 0; i < opNum; ++i)
		{
			std::string op = random_OP();
			ops.push_back(op);
		}

		int bracketNum = random_Int(0, opNum - 1);
		
		std::string infix = "";
		if (opNum == 1)
		{
			infix += numbers[0].to_string() + ops[0] + numbers[1].to_string();
		}
		else if (opNum == 2)
		{
			if (bracketNum == 1)
			{
				int position = random_Int(0, 1);
				if (position == 0)
				{
					infix += "(" + numbers[0].to_string()  + ops[0]  + numbers[1].to_string() + ")";
					infix += ops[1] + numbers[1].to_string();
				}
				else
				{
					infix += numbers[0].to_string() + ops[0];
					infix += "(" + numbers[1].to_string() + ops[1] + numbers[2].to_string() + ")";
				}
			}
			else if(bracketNum==0)
			{
				infix += numbers[0].to_string() + ops[0] + numbers[1].to_string() + ops[1] + numbers[2].to_string();
			}
		}
		else if (opNum == 3)
		{
			if (bracketNum == 0)
			{
				infix += numbers[0].to_string() + ops[0] + numbers[1].to_string() + ops[1] + numbers[2].to_string()+ops[2]+numbers[3].to_string();
			}
			else if (bracketNum == 1)
			{
				int position = random_Int(0, 2);
				if (position == 0)
				{
					infix += "(" + numbers[0].to_string() + ops[0] + numbers[1].to_string() + ")";
					infix += ops[1] + numbers[1].to_string() + numbers[2].to_string() + ops[2] + numbers[3].to_string();
				}
				else if (position == 1)
				{
					infix += numbers[0].to_string() + ops[0];
					infix += "(" + numbers[1].to_string() + ops[1] + numbers[2].to_string() + ")";
					infix += ops[2] + numbers[3].to_string();
				}
				else if (position ==  2)
				{
					infix += numbers[0].to_string() + ops[0] + numbers[1].to_string();
					infix += ops[1] + "(" + numbers[2].to_string() + ops[2] + numbers[3].to_string() + ")";
				}
			}
			else if (bracketNum == 2)
			{
				infix += "(" + numbers[0].to_string() + ops[0] + numbers[1].to_string() + ")";
				infix += ops[1] + "(" + numbers[2].to_string() + ops[2] + numbers[3].to_string() + ")";
			}
		}
		


		if (IsCreaateNegative(infix) || IsDownZero(infix))			//过程不能有负数以及除0
		{
			continue;
		}
		std::string answer = mCalculator.GetResult(infix);
		bool flag = false;
		for (size_t i = 0; i < mAnswers.size(); ++i)
		{
			if (mAnswers[i]._Equal(answer) && IsSimilary(infix, mInfixs[i]))
			{
				flag = true;
				break;
			}
		}

		if (!flag)
		{
			mInfixs.push_back(infix);
			mAnswers.push_back(answer);
			++i;
		}
	}
	SaveTitleToFile();
	SaveAnswerToFile();
}

bool PriAriCreator::ReadTitilesAndAnswer(std::string titlefilename, std::string answerfilename)
{
	//先清空
	mInfixs.clear();
	mAnswers.clear();

	std::ifstream is;
	is.open(titlefilename,std::ios::in);
	if (!is.is_open())
	{
		std::cout << titlefilename + "文件不存在!!!" << std::endl;
		return false;
	}
	//读取文件
	std::string  line;
	while (std::getline(is, line))
	{
		std::string back = line.substr(line.find(":") + 1);
		std::string infix = back.substr(0, back.find("="));
		mInfixs.push_back(infix);
	}
	is.close();

	is.open(answerfilename, std::ios::in);
	if (!is.is_open())
	{
		std::cout << answerfilename + "文件不存在!!!" << std::endl;
		return false;
	}

	//读取文件
	while (std::getline(is, line))
	{
		std::string answer = line.substr(line.find(":") + 1);
		//清除空格
		size_t postion = answer.find(" ");
		while (postion != -1)
		{
			answer.erase(postion, 1);
			postion= answer.find(" ");
		}
		mAnswers.push_back(answer);
	}
	is.close();
	return true;
}

void PriAriCreator::VerificationAnswer()
{
	std::ofstream os;
	os.open("Grade.txt", std::ios::out);
	std::vector<std::string> currIndex;
	std::vector<std::string> errIndex;
	for (size_t i = 0; i < mInfixs.size(); ++i)
	{
		std::string result = mCalculator.GetResult(mInfixs[i]);
		if (mAnswers[i]._Equal(result))
		{
			currIndex.push_back(std::to_string(i + 1));
		}
		else
		{
			errIndex.push_back(std::to_string(i + 1));
		}
	}


	std::string contextCurr = "Correct: ";
	if (currIndex.size() > 0)
	{
		contextCurr += std::to_string(currIndex.size()) + " (";
		for (size_t i = 0; i < currIndex.size() - 1; ++i)
		{
			contextCurr += currIndex[i] + ",";
		}
		contextCurr += currIndex.back() + ")";
	}
	else
	{
		contextCurr += "0";
	}
	os << contextCurr << std::endl;

	std::string contextErr = "Wrong: ";
	if (errIndex.size() > 0)
	{
		contextErr += std::to_string(errIndex.size()) + " (";
		for (size_t i = 0; i < errIndex.size() - 1; ++i)
		{
			contextErr += errIndex[i] + ",";
		}
		contextErr += errIndex.back() + ")";
	}
	else
	{
		contextErr += "0";
	}
	os << contextErr << std::endl;
	os.close();
}

bool PriAriCreator::IsSimilary(std::string scource, std::string destination)
{
	//获取后缀表达式
	std::stack<std::string> RP1 = mCalculator.GetReversePolish(scource);
	std::stack<std::string> RP2 = mCalculator.GetReversePolish(destination);

	//得到子表达式
	std::vector<std::vector<std::string>> ex1 = mCalculator.GetChildExpression(RP1);
	std::vector<std::vector<std::string>> ex2 = mCalculator.GetChildExpression(RP2);

	for (auto& p : ex1)
	{
		for (auto& v : ex2)
		{
			if (Cmp_ExChild(p, v))
			{
				return true;
			}
		}
	}
	return false;
}

bool PriAriCreator::IsCreaateNegative(std::string expression)
{
	//获取后缀表达式
	std::stack<std::string> pr = mCalculator.GetReversePolish(expression);

	//得到子表达式
 	std::vector<std::vector<std::string>> ex = mCalculator.GetChildExpression(pr);

	for (auto& p:ex)
	{
		std::string result = mCalculator.CalResult(p[1], p[0], p[2]);
		if (result.find("-")!=-1)
		{
			return true;
		}
	}
	return false;
}

bool PriAriCreator::IsDownZero(std::string expression)
{
	//获取后缀表达式
	std::stack<std::string> pr = mCalculator.GetReversePolish(expression);

	//得到子表达式
	std::vector<std::vector<std::string>> ex = mCalculator.GetChildExpression(pr);

	for (auto& p : ex)
	{
		if (p[0] == "0" && p[2] == "#")
		{
			return true;
		}
	}
	return false;
}

bool PriAriCreator::Cmp_ExChild(std::vector<std::string> ex1, std::vector<std::string> ex2)
{
	if (ex1[2] == ex2[2])
	{
		if (ex1[0] == ex2[1] || (ex1[0] == ex2[0] && ex1[1] == ex2[1]))
		{
			return true;
		}
	}
	return false;
}

long long PriAriCreator::random_LL(long long min, long long max, unsigned int seed)
{
	std::uniform_int_distribution<long long> uid(min, max);
	return uid(mDre);
}

int PriAriCreator::random_Int(int min, int max, unsigned int seed)
{
	std::uniform_int_distribution<int> uid(min, max);
	return uid(mDre);
}

std::string PriAriCreator::random_OP()
{
	int i = random_Int(0, 3);
	switch (i)
	{
	case 0:return " + ";
	case 1:return " - ";
	case 2:return " * ";
	case 3:return " ÷ ";
	default:
		return "";
	}
}

std::string PriAriCreator::CreateAnswer(std::string infix)
{
	return mCalculator.GetResult(infix);
}

void PriAriCreator::SaveTitleToFile()
{
	mTitleFile.open("Exercises.txt", std::ios::out);
	//mTitleFile << "####################################" << std::endl;
	for (size_t i = 0; i < mInfixs.size(); i++)
	{
		std::string str = "";
		char logStr[10]{};
		sprintf_s(logStr, "%d: ", static_cast<int>(i + 1));
		str += logStr+ mInfixs[i] + " = ";
		mTitleFile << str << std::endl;
	}
}

void PriAriCreator::SaveAnswerToFile()
{
	mAnswerFile.open("Answers.txt", std::ios::out);
	//mAnswerFile << "####################################" << std::endl;
	for (size_t i = 0; i < mAnswers.size(); i++)
	{
		std::string str = "";
		char logStr[10]{};
		sprintf_s(logStr, "%d: ", static_cast<int>(i + 1));
		str += logStr + mAnswers[i];
		mAnswerFile << str << std::endl;
	}
}

