#pragma once
#include "Obj.h"

class Door :
	public Obj
{
public:
	
	Door();
	Door(double x, double y, bool die);
	~Door();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Door;
	};
	int OpendoorSE_;		//���̌��ʉ�
	bool actionflag_;
};

