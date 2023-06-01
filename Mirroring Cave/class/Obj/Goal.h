#pragma once
#include "Obj.h"
class Goal :
    public Obj
{
public:
	static constexpr int Goaloffset = 10;
	Goal();
	Goal(double x, double y, bool die);
	~Goal();

private:
	bool Init()override;
	
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Goal;
	};
	int animeCnt_;	//ゴールのアニメーションカウント
};

