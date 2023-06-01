#pragma once
#include "Obj.h"
class Pushbutton :
    public Obj
{
public:
	Pushbutton();
	Pushbutton(double x, double y, bool die);
	~Pushbutton();

private:
	bool Init()override;

	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Pushbutton;
	};
};

