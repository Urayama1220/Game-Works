#include <DxLib.h>
#include "../common//imageMng.h"
#include "Hole.h"
Hole::Hole()
{
	Init();
}
Hole::Hole(double x, double y, bool die)
{
	Init(x,y, die);
}
Hole::~Hole()
{
}

bool Hole::Init()
{
	Obtype_ = objType::Hole;
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//âºÉTÉCÉY
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/hole.png", "Hole");
	return false;
}



bool Hole::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Hole::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	/*if (!moveStop_checkdie_flag)
	{
		if (CollideH()(pos_, size_, objList_, tmxObj_))
		{
			moveStop_checkdie_flag = true;
		}
	}*/
}

void Hole::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
			static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Hole")[0], true);

}
