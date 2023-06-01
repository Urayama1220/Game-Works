#pragma once
#include "Obj.h"
class OneWay :
    public Obj
{
public:
	OneWay();
	OneWay(double x, double y, bool die, MOVE_DIRECTION dir);
	~OneWay();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::OneWay;
	};
};

