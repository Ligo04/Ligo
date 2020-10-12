#include "Frac.h"
#include<iostream>
Frac::Frac()
	:m_Up(0),m_Down(1)
{
}

Frac::Frac(long long molecule, long long denominator)
	:m_Up(molecule),m_Down(denominator)
{
	Simplify();
}

Frac::Frac(std::string ex)
{
	size_t position = ex.find("/");
	if (position != -1)
	{
		std::string front = ex.substr(0, position);	//前半段
		std::string back = ex.substr(position+1);	//后半段
		position = front.find("'");
		std::string::size_type st;
		m_Down = std::stoll(back, &st);
		if (position != -1)
		{
			std::string mul_s = front.substr(0, position);
			std::string up_s= front.substr(position + 1);
			long long mul_num = std::stoll(mul_s,&st);
			m_Up = std::stoll(up_s, &st) + mul_num * m_Down;
		}
		else
		{
			m_Up = std::stoll(front, &st);
		}
	}
	else
	{
		std::string::size_type st;
		m_Up = std::stoll(ex, &st);
		m_Down = 1;
	}
	Simplify();
}

Frac::~Frac()
{
}

Frac Frac::operator+(const Frac& right) const
{
	Frac result;
	result.m_Up = m_Up * right.m_Down + right.m_Up * m_Down;
	result.m_Down = m_Down * right.m_Down;
	result.Simplify();
	return result;
}

Frac Frac::operator-(const Frac& right) const
{
	Frac result;
	result.m_Up = m_Up * right.m_Down - right.m_Up * m_Down;
	result.m_Down = m_Down * right.m_Down;
	result.Simplify();
	return result;
}

Frac Frac::operator*(const Frac& right) const
{
	Frac result;
	result.m_Up = m_Up * right.m_Up;
	result.m_Down = m_Down * right.m_Down;
	result.Simplify();
	return result;
}

Frac Frac::operator/(const Frac& right) const
{
	Frac result;
	if (right.m_Up == 0)
	{
		result.m_Up = 0;
		result.m_Down = 1;
		return result;
	}
	result.m_Up = m_Up * right.m_Down;
	result.m_Down = m_Down * right.m_Up;
	result.Simplify();
	return result;
}

bool Frac::operator==(const Frac& right) const
{
	if ((m_Up / m_Down) == (right.m_Up / right.m_Down)&& (m_Up % m_Down) == (right.m_Up % right.m_Down))
		return true;
	return false;
}

bool Frac::operator!=(const Frac& right) const
{
	return !operator==(right);
}


std::string Frac::to_string() const
{

	std::string str;
	if (m_Up == 0)
	{
		str = "0";
		return str;
	}
	//先化简
	long long multiple = abs(m_Up / m_Down);
	long long remainder = abs(m_Up % m_Down);
	if (multiple != 0)
	{
		if (m_Up > 0)
		{
			str += std::to_string(multiple);
		}
		else
		{
			str+="-"+ std::to_string(multiple);
		}
		if (remainder != 0)
		{
			str += "'" + std::to_string(remainder) + "/" + std::to_string(m_Down);
		}
	}
	else
	{
		str += std::to_string(remainder) + "/" + std::to_string(m_Down);
	}
	return str;
}

void Frac::Simplify()
{
	if (m_Down < 0)	//分母小于零，分子分母取为相反数
	{
		m_Up = -m_Up;
		m_Down = -m_Down;
	}

	if (m_Up == 0)	//分子为零
	{
		m_Down = 1;		//令分母为1
	}
	else              //分子不为零
	{
		long long divisor = MaxDiviSor(abs(m_Up), abs(m_Down));
		m_Up /= divisor;
		m_Down /= divisor;
	}
}

long long Frac::MaxDiviSor(long long a, long long b)
{
	unsigned long long i = 0;
	while (b!=0)
	{
		i = a % b;
		a = b;
		b = i;
	}
	return a;
}
