#pragma once
#include "Obj.h"
class Hole :
	public Obj
{
public:
	Hole();
	Hole(double x, double y, bool die);
	~Hole();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Hole;
	};

};

