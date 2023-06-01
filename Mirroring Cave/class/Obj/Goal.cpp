#include <DxLib.h>
#include "../common/imageMng.h"
#include "Goal.h"

Goal::Goal()
{
	Init();
}

Goal::Goal(double x, double y, bool die)
{
	Init(x, y, die);
}

Goal::~Goal()
{
}

bool Goal::Init()
{
	Obtype_ = objType::Goal;
	pos_ = {0,0 };
	size_ = { square_size,square_size };//âºÉTÉCÉY
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/Goal.png", "Goal", { 64,112 }, { 3,4 });
	lpImageMng.GetID("image/Obj/Re.png", "Re");
	animeCnt_ = 0;
	return false;
}



bool Goal::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Goal::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	animeCnt_++;
}

void Goal::Draw(void)
{
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Re")[0], true);
	DrawExtendGraph(static_cast<int>(pos_.x- Goaloffset), static_cast<int>(pos_.y - size_.y- Goaloffset), static_cast<int>(pos_.x+size_.x-1+ Goaloffset), static_cast<int>(pos_.y+size_.y-1+ Goaloffset), lpImageMng.GetID("Goal")[(animeCnt_ / 40)%3+9], true);
}
