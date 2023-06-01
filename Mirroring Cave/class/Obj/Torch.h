#pragma once
#include "Obj.h"
constexpr int Calculated_value = 3; //アニメーションための定数
class Torch :
	public Obj
{
public:
	Torch();
	Torch(double x, double y, bool die);
	~Torch();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Torch;
	};
	bool  minusflag_; //松明がついていたら開くドアのフラグ
	bool  minusOPflag_;//松明が消えたら開くドアのフラグ
	int animCnt_;	//アニメーションカウント
};

