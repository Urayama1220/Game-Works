#pragma once
#include "Obj.h"
constexpr int Calculated_value = 3; //�A�j���[�V�������߂̒萔
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
	bool  minusflag_; //���������Ă�����J���h�A�̃t���O
	bool  minusOPflag_;//��������������J���h�A�̃t���O
	int animCnt_;	//�A�j���[�V�����J�E���g
};

