#include "Calculator.h"

Calculator::Calculator()
	:number{}
{
}

Calculator::~Calculator()
{

}

bool Calculator::Priority(char t_in, char t_out)
{
	int pri_in, pri_out;
	switch (t_in)
	{
	case '(':
	case ')':pri_in = 1; break;
	case '+':
	case '-':pri_in = 2; break;
	case '*':
	case '#':pri_in = 3; break;
	default:pri_in = 0;
		break;
	}
	switch (t_out)
	{
	case '(':
	case ')':pri_out = 1; break;
	case '+':
	case '-':pri_out = 2; break;
	case '*':
	case '#':pri_out = 3; break;
	default:
		pri_out = 0;
		break;
	}
	if (pri_in >= pri_out)
	{
		return true;  //栈顶大于等于当前 true
	}
	else
	{
		return false;  //栈顶小于当前 false
	}
}

bool Calculator::IsOp(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '#' || op == '(' || op == ')')
	{
		return true;
	}
	return false;
}

bool Calculator::IsOp(std::string op)
{
	if (op._Equal("+") || op._Equal("-") || op._Equal("*") || op._Equal("#") ||op._Equal("(") || op._Equal(")"))
	{
		return true;
	}
	return false;
}

std::string Calculator::SuppleInfix(std::string infix)
{
	std::string result = infix;
	//清除所有空格
	size_t position = result.find(" ");
	while (position!=-1)
	{
		result.erase(position, 1);
		position = result.find(" ");
	}
	//替换
	position = result.find("÷");
	while (position != -1)
	{
		result.replace(position,2,"#");
		position = result.find("÷");
	}

	//补充完整中缀表达式(补零)
	if ((result.at(0) == '-') && (result.at(1) >= '0' && result.at(1) <= '9'))
	{
		result.insert(result.begin(), '0');
	}
	for (size_t i = 0; i < result.length(); ++i)
	{
		if ((result.at(i) == '(') && (result.at(i + 1) == '+' || result.at(i + 1) == '-'))
		{
			std::string str = "0";
			result.insert(i+1, str);
		}
	}
	return result;
}

bool Calculator::ReversePolish(std::string infix)
{
	if (infix.empty())
	{
		return false;
	}
	std::stack<std::string> num_t;
	std::stack<char> op;
	while (!number.empty())
	{
		number.pop();
	}
	infix = SuppleInfix(infix);

	for (size_t i = 0; i < infix.length();)
	{
		if (infix.at(i) >= '0' && infix.at(i) <= '9')
		{
			std::string num;
			while (i < infix.length() && !IsOp(infix.at(i)))
			{
				num += infix.at(i++);
			}
			num_t.push(num);
		}
		if (i < infix.length() && IsOp(infix.at(i)))
		{
			if (op.empty())
			{
				op.push(infix.at(i));
			}
			else
			{
				if (infix.at(i) == ')')
				{
					//'('匹配失败直接
					if (op.empty())
					{
						return false;
					}

					std::string str;
					char top = op.top(); 
					op.pop();
					while (top != '(' && !op.empty())
					{
						str = top;
						num_t.push(str);
						top = op.top();
						op.pop();
					}

					if (top != '(')
					{
						return false;	//匹配失败
					}
				}
				else
				{
					if (infix.at(i) == '(' || !Priority(op.top(), infix.at(i)))			//'('或空或栈顶小于当前的
					{
						op.push(infix.at(i));
					}
					else                         //如果栈顶元素运算符优先级>= 当前元素的优先级，出栈并把运算符压到数字栈中直到栈顶元素优先级<当前元素优先级，然后当前元素压到当前的运算符栈中；
					{
						std::string str;
						char top;
						do
						{
							top = op.top();
							op.pop();
							str = top;
							num_t.push(str);
						} while (!op.empty()&&Priority(op.top(), infix.at(i)));
						op.push(infix[i]);
					}
				}
			}
			++i;
		}
	}

	char top;
	std::string str;
	while (!op.empty())
	{
		top = op.top();
		op.pop();
		str = top;
		num_t.push(str);
	}
	while (!num_t.empty())
	{
		str = num_t.top();
		number.push(str);
		num_t.pop();
	}
	return true;
}

std::string Calculator::CalcuReversePolish()
{
	if (number.empty())
	{
		return "";
	}
	std::stack<Frac>* temp = new std::stack<Frac>;
	std::string str;
	while (!number.empty())
	{
		str = number.top();
		number.pop();
		if (!IsOp(str))
		{
			Frac frac(str);
			temp->push(frac);
		}
		else
		{
			if (temp->size() > 1)
			{
				Frac first, second;
				first = temp->top();
				temp->pop();
				second = temp->top();
				temp->pop();

				char c_op = str.at(0);

				switch (c_op)
				{
				case '+':
					second = second + first;
					temp->push(second);
					break;
				case '-':
					second = second - first;
					temp->push(second);
					break;
				case '*':
					second = second * first;
					temp->push(second);
					break;
				case '#':
					if (first == Frac(0, 1))
					{
						return std::string("X");   //	X代表无结果
					}
					second = second / first;
					temp->push(second);
					break;
				default:
					break;
				}
			}
		}
	}
	Frac result = temp->top();
	temp->pop();
	delete temp;
	return result.to_string();
}

std::stack<std::string> Calculator::GetReversePolish(std::string infix)
{
	if (ReversePolish(infix))
	{
		return number;
	}
	return std::stack<std::string>();
}

std::vector<std::vector<std::string>> Calculator::GetChildExpression(std::stack<std::string> reversePolish)
{
	std::vector<std::vector<std::string>> childEx;
	std::stack<std::string> stack;
	while(!reversePolish.empty())
	{
		std::string top = reversePolish.top();
		if (!IsOp(top))
		{
			stack.push(top);
			reversePolish.pop();
		}
		else
		{
			std::vector<std::string> child;

			std::string num1 = stack.top();
			child.push_back(num1);
			stack.pop();
			std::string num2 = stack.top();
			child.push_back(num2);
			stack.pop();
			child.push_back(top);
			reversePolish.pop();

			childEx.push_back(child);
			stack.push(CalResult(child[1], child[0], child[2]));
		}
	}
	return childEx;
}

std::string Calculator::CalResult(std::string num1, std::string num2, std::string op)
{
	Frac Frac1(num1);
	Frac Frac2(num2);
	Frac result;
	char opc = op.at(0);
	switch (opc)
	{
	case '+':
		result = Frac1 + Frac2;
		break;
	case '-':
		result = Frac1 - Frac2;
		break;
	case '*':
		result = Frac1 * Frac2;
		break;
	case '#':
		if (Frac2 == Frac(0, 1))
		{
			break;
		}
		result = Frac1 / Frac2;
		break;
	default:
		break;
	}
	return result.to_string();
}

std::string Calculator::GetResult(std::string infix)
{
	if(ReversePolish(infix))
		return CalcuReversePolish();
	return std::string("");
}
