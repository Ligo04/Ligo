#ifndef __CALCULATOR_H
#define __CALCULATOR_H
#include<string>
#include<stack>
#include<vector>
#include"Frac.h"

class Calculator
{
public:
	Calculator();
	~Calculator();
	
	//判断符合优先级
	bool Priority(char t_in, char t_out);
	//判断是否是符号
	bool IsOp(char op);
	bool IsOp(std::string op);
	/// <summary>
	/// 补充完整中缀表达式
	/// </summary>
	/// <param name="infix"></param>
	/// <returns>返回补零后的中缀表达式</returns>
	std::string SuppleInfix(std::string infix);

	/// <summary>
	/// 中缀表达式转成后缀表达式
	/// </summary>
	/// <param name="infix"></param>
	/// <returns>是否转换成功，若不匹配，则返回false</returns>
	bool ReversePolish(std::string infix);

	/// <summary>
	/// 计算逆波兰结果
	/// </summary>
	/// <returns>返回结果，若后缀错误，则返回空</returns>
	std::string CalcuReversePolish();

	/// <summary>
	/// 得到后缀表达式栈
	/// </summary>
	/// <param name="infix"></param>
	/// <returns>栈</returns>
	std::stack<std::string>  GetReversePolish(std::string infix);

	/// <summary>
	/// 根据后缀表达式得到一个子表达式的二维数组
	/// </summary>
	/// <param name="reversePolish"></param>
	/// <returns>子表达式的二维数组</returns>
	std::vector<std::vector<std::string>> GetChildExpression(std::stack<std::string> reversePolish);


	std::string CalResult(std::string num1, std::string num2, std::string op);
	/// <summary>
	/// 输入中缀得到结果
	/// </summary>
	/// <param name="infix"></param>
	/// <returns>计算结果</returns>
	std::string GetResult(std::string infix);
private:
	std::stack<std::string> number;						//存储后缀表达式
};

#endif // !__CALCULATOR_H
