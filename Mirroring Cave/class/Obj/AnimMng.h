#pragma once
#include "Obj.h"
#include <string>
#include <map>
#include <list>
#define lpAnimMng AnimMng::GetInstance()

using AnimData = std::array<int, 2>;
using AnimCm = std::pair<int, int>;
using AnimLpCm = std::pair<int, AnimCm>;
using  AnimNode = std::pair<AnimLpCm, std::list<AnimData>>;
using AnimMap = std::map<std::string, AnimNode>;

using animItr = std::list<AnimData >::iterator;

constexpr int GraphHD = 0;
constexpr int InvLimit = 1;
constexpr int collision = 2;

struct animItrCnt
{
	std::string ObjID;
	std::string state;
	animItr animitr;
	unsigned int stateCnt_;
	int animPlayCnt_;
};

class AnimMng 
{
public:
	static AnimMng& GetInstance()
	{
		static AnimMng s_Instance;
		return s_Instance;
	};
	//bool Init(std::string state);
	bool UpdataAnime(animItrCnt& animItr);
	bool LoadAnim(std::string filName);
	Vector2Dbl divsize;
	/*void SetAnim(std::string state_);*/
	animItrCnt SetAnimData(std::string ObjID, std::string state_);
private:
	
	AnimMng();
	~AnimMng();
	
	AnimMap AnimTbl;
	animItrCnt animItrCnt_;
};

