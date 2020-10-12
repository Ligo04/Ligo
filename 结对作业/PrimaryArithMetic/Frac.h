#ifndef __FRAC_H
#define __FRAC_H
#include<string>

class Frac
{
public:
	Frac();
	Frac(long long molecule, long long denominator);
	Frac(std::string ex);
	~Frac();

	Frac operator+(const Frac& right) const;
	Frac operator-(const Frac& right) const;
	Frac operator*(const Frac& right) const;
	Frac operator/(const Frac& right) const;

	bool operator==(const Frac& right) const;
	bool operator!=(const Frac& right) const;

	//化简
	void Simplify();

	long long MaxDiviSor( long long a,  long long b);
	//转换为字符串
	std::string to_string() const;
private:

	long long m_Up;					//分子
	long long m_Down;				//分母
};

#endif // !__FRAC_H
