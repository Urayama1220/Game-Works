#pragma once
#include "Obj.h"
class Half :
    public Obj
{
public:
	Half();
	Half(double x, double y, bool die);
	~Half();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Half;
	};
};

