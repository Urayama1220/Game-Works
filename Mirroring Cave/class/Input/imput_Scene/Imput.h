#pragma once
#include <map>
#include <string>

enum class ImputType
{
	NOW,
	OLD
};

using ImputData = std::map<std::string, int>;

class Imput
{
public:
	Imput();
	virtual ~Imput();
	virtual bool Updata() = 0;
	/*virtual bool Updata(Obj& obj, Obj& other) { return false; };*/
	const ImputData& GetData(ImputType type);
private:

protected:
	ImputData data_;
	ImputData dataOld_;

};

