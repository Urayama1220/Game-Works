#pragma once
#include "Obj.h"
class Simultaneous :
	public Obj
{
public:
	Simultaneous();
	Simultaneous(double x, double y, bool die);
	~Simultaneous();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Simultaneous;
	};
	bool  minusflag_;
};

