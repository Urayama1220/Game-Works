#pragma once
#include "Obj.h"
class Simultaneousdoor :
	public Obj
{
public:
	Simultaneousdoor();
	Simultaneousdoor(double x, double y, bool die);
	~Simultaneousdoor();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Simultaneousdoor;
	};
	bool actionflag;
	int OpendoorSE_;		//ƒhƒA‚ÌŒø‰Ê‰¹
};

