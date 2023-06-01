#pragma once
#include "Obj.h"
class PushDoor :
    public Obj
{
public:
	PushDoor();
	PushDoor(double x, double y, bool die);
	~PushDoor();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::PushDoor;
	};
	int OpendoorSE_;		//ƒhƒA‚ÌŒø‰Ê‰¹
	bool actionflag_;
	int ecSE;
};

