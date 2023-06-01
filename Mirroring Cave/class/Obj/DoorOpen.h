#pragma once
#include "Obj.h"

class DoorOpen :
	public Obj
{
public:
	DoorOpen();
	DoorOpen(double x, double y, bool die);
	~DoorOpen();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::DoorOpen;
	};
	bool actionflag_;
	int die_alive_CntMax_;  //€‚Ê‚±‚Æ‚Ì‚Å‚«‚é¼–¾‚ÌÅ‘å”;
	int OpendoorSE_;		//“¹‚ÌŒø‰Ê‰¹
};

