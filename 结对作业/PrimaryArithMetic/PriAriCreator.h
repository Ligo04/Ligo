#ifndef __PRIARICREATOR
#define __PRIARICREATOR
#include<fstream>
#include<random>
#include<time.h>
#include<string>
#include"Calculator.h"

class PriAriCreator
{
public:
	PriAriCreator();
	~PriAriCreator();

	/// <summary>
	/// 生成题目(题目数量，自然数范围，真分数范围和真分数分母)
	/// </summary>
	/// <param name="titleNums"></param>
	/// <param name="naturlrange"></param>
	/// <param name="uprange"></param>
	/// <param name="downrange"></param>
	void CreateAriTitlesAndAnswer(int titleNums = 10, long long naturlrange = 10, long long fracrange = 4, long long downrange = 10);
	
	/// <summary>
	/// 读取文件的题目
	/// </summary>
	/// <param name="titlesname"></param>
	bool ReadTitilesAndAnswer(std::string titlefilename,std::string answerfilename);

	/// <summary>
	/// 验证答案
	/// </summary>
	void VerificationAnswer();

	/// <summary>
	/// 判断题目是否相似
	/// </summary>
	/// <param name="scource"></param>
	/// <param name="destination"></param>
	/// <returns>bool</returns>
	bool IsSimilary(std::string scource,std::string destination);

	bool IsCreaateNegative(std::string expression);

	bool IsDownZero(std::string expression);
	/// <summary>
	/// 判断两个表达式是否等价
	/// </summary>
	/// <param name="exp"></param>
	/// <param name="exp2"></param>
	/// <returns>bool</returns>
	bool Cmp_ExChild(std::vector<std::string> ex1, std::vector<std::string>ex2);

	long long random_LL(long long min, long long max, unsigned int seed = time(nullptr));

	int random_Int(int min, int max, unsigned int seed = time(nullptr));

	std::string random_OP();

	std::string CreateAnswer(std::string infix);

	void SaveTitleToFile();
	void SaveAnswerToFile();
private:
	Calculator	mCalculator;								//计算器
	const int mOpNumMax = 3;								//最大运算符数量
	std::vector<std::string>	mInfixs;					//生成的题目
	std::vector<std::string>	mAnswers;					//题目的答案


	std::ofstream  mTitleFile;								//题目文件流
	std::ofstream  mAnswerFile;								//答案文件流

	std::default_random_engine mDre;
};
#endif // !__PRIARICREATOR
