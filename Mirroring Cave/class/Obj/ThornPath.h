#pragma once
#include "Obj.h"
class ThornPath :
    public Obj
{
public:
	ThornPath();
	ThornPath(double x, double y, bool die);
	~ThornPath();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::ThornPath;
	};

};

