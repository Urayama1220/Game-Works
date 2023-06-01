#pragma once
#include <vector>
#include <string>
#include <map>
#include "Vector2.h"

#define lpImageMng imageMng::GetInstance()
using VecInt = std::vector<int>;
class imageMng
{
public:
	static imageMng& GetInstance()
	{
		static imageMng s_Instance;
		return (s_Instance);
	}
	const VecInt& GetID(std::string key);
	const VecInt& GetID(std::string f_name , std::string key);
	const VecInt& GetID(std::string f_name,std::string key,Vector2 divsize,Vector2 divCnt);
private:
	imageMng();
	~imageMng();
	std::map<std::string, VecInt>imageMap_;
};

