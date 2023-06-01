#pragma once
#include "Obj.h"
constexpr int Calculated_value = 3;
class TorchOpen :
	public Obj
{
public:
	TorchOpen();
	TorchOpen(double x, double y);
	~TorchOpen();

private:
	bool Init(double x, double y)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::TorchOpen;
	};
	bool  minusflag_;
	int animCnt_;
};

