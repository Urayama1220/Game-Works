#include <DxLib.h>
#include "../common//imageMng.h"
#include "ThornPath.h"
ThornPath::ThornPath()
{
	Init();
}
ThornPath::ThornPath(double x, double y, bool die)
{
	Init(x, y, die);
}
ThornPath::~ThornPath()
{
}

bool ThornPath::Init()
{
	Obtype_ = objType::ThornPath;
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//âºÉTÉCÉY
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/thorn.png", "thorn");
	return false;
}


bool ThornPath::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void ThornPath::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	
}

void ThornPath::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
			static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	//DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("thorn")[0], true);
	DrawExtendGraph(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x + square_size),
		static_cast<int>(pos_.y + square_size) , lpImageMng.GetID("thorn")[0], true);
}