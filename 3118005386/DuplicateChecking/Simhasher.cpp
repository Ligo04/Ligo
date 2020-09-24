#include "Simhasher.h"
#include <iomanip>
const double PI = std::atan(1.0) * 4;
#pragma warning(disable:26451)
#pragma warning(disable:4267)
// std::string 转换为 UTF-8 编码
std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

std::string UtfToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

bool IsErase(int i)
{
	if (isspace(i))
	{
		return true;
	}
	return false;
}

uint64_t binaryStringToUint64(const std::string& bin)
{
	uint64_t res = 0;
	for (size_t i = 0; i < bin.size(); i++)
	{
		res <<= 1;
		if (bin[i] == '1')
		{
			res += 1;
		}
	}
	return res;
}

Simhasher::Simhasher(const char* _DICT_PATH, const char* _HMM_PATH, const char* _USER_DICT_PATH, const char* _IDF_PATH, const char* _STOP_WORD_PATH)
	:mJieba(_DICT_PATH, _HMM_PATH, _USER_DICT_PATH, _IDF_PATH, _STOP_WORD_PATH), mFiles{}
{
}

Simhasher::~Simhasher()
{
	mLog.close();
};

bool Simhasher::Parse(int nums, char** argv)
{
	mFiles.resize(nums - 1);
	std::ifstream is;
	std::stringstream oss;
	//读取文件的数据
	for (int i = 0; i < nums - 1; ++i)
	{
		is.open(argv[i + 1], std::ios::in);
		if (!is.is_open())
		{
			std::cout << "打开" << argv[i + 1] << "失败\n";
			return false;
		}
		oss << is.rdbuf();
		mFiles[i].first = std::string(argv[i + 1]);
		mFiles[i].second = oss.str();
		//清除空格
		mFiles[i].second.erase(std::remove_if(mFiles[i].second.begin(), mFiles[i].second.end(), IsErase), mFiles[i].second.end());
		//std::cout << UtfToGbk(mFiles[i].second.c_str()) << std::endl;
		oss.clear();
		is.close();
	}
	//is.close();

	mLog.open(argv[nums], std::ios::out | std::ios::app);
	if (!mLog.is_open())
	{
		std::cout << "打开" << argv[nums] << "失败\n";
		return false;
	}
	return true;
}

void Simhasher::isSimilarity(uint32_t topk, unsigned int n)
{
	std::vector<uint64_t> nums;
	for (auto& p : mFiles)
	{
		std::vector<std::pair<uint64_t, int>> fw;
		fw = Participle(p.second, topk);
		nums.push_back(CalculaterSimhash(fw));
	}

	//两两比较(当然现在只有两个文件)
	for (size_t i = 0; i < nums.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < nums.size(); ++j)
		{
			std::pair<bool, double> flag = CalcularSimilarity(nums[i], nums[j], n);
			if (flag.first)
			{
				std::string str = "文件1:" + mFiles[i].first + " 与 文件二:" + mFiles[j].first + " 相似,相似度:";
				char logStr[100]{};
				sprintf_s(logStr, "%.2f", flag.second);
				str += logStr;
				std::cout << str << std::endl;
				mLog << str << std::endl;
			}
			else
			{
				std::string str = "文件1:" + mFiles[i].first + " 与 文件二:" + mFiles[j].first + " 不相似,相似度:";
				char logStr[100]{};
				sprintf_s(logStr, "%0.2f", flag.second);
				str += logStr;
				std::cout << str << std::endl;
				mLog << str << std::endl;
			}
		}
	}
}

std::vector<std::pair<uint64_t, int>> Simhasher::Participle(std::string context, uint32_t topk)
{
	//提取关键词
	std::vector<cppjieba::KeywordExtractor::Word> words;
	mJieba.extractor.Extract(context, words, topk);


	std::vector<std::pair<uint64_t, int>> fweight;
	std::hash<std::string> hash;

	//计算哈希值与权重(词频)
	for (auto& w : words)
	{
		std::pair<uint64_t, int> pairs;
		pairs.first = hash(w.word);
		pairs.second = static_cast<int>(w.weight);
		fweight.push_back(pairs);
	}
	return fweight;
}

uint64_t Simhasher::CalculaterSimhash(std::vector<std::pair<uint64_t, int>> fw)
{
	std::vector<std::vector<int>> numMatrix;
	//加权
	for (auto& p : fw)
	{
		std::vector<int> addWeight(64);
		for (size_t i = 0; i < 64; ++i)
		{
			if ((p.first >> i) & 1)
			{
				addWeight[i] = p.second * 1;
			}
			else
			{
				addWeight[i] = p.second * (-1);
			}
		}
		numMatrix.push_back(addWeight);
	}
	std::string str;
	//合并,降维
	for (size_t i = 0; i < 64; ++i)
	{
		double total = 0;
		for (auto& p : numMatrix)
		{
			total += p[i];
		}

		total >= 0 ? str += "1" : str += "0";
	}

	//输出结果
	return binaryStringToUint64(str);
}

std::pair<bool, double> Simhasher::CalcularSimilarity(uint64_t lhs, uint64_t rhs, unsigned short n)
{
	std::pair<bool, double> flag;
	unsigned short cnt = std::bitset<64>(lhs ^ rhs).count();
	cnt <= n ? flag.first = true : flag.first = false;
	//计算相似度
	flag.second = (1.0 / sqrt(2 * PI * 0.16)) * exp(-std::pow((0.01 * cnt - 0.01), 2) / (2 * std::pow(0.0459, 2)));
	return flag;
}
