#include <DxLib.h>
#include "../common/imageMng.h"
#include "hint.h"
hint::hint()
{
	Init();
}
hint::hint(double x, double y, bool die,std::string hintId)
{
	hintId_ = hintId;
	lpImageMng.GetID(hintId_);
	sizeAdd_ = {0,0};
	Init(x, y, die);
}
hint::hint(double x, double y, bool die, std::string hintId, Vector2Dbl Addsize)
{
	hintId_ = hintId;
	lpImageMng.GetID(hintId_);
	sizeAdd_ = Addsize;
	Init(x, y, die);
}
hint::~hint()
{
}

bool hint::Init()
{
	Obtype_ = objType::hint;
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//âºÉTÉCÉY
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/R.png", "R.png");
	lpImageMng.GetID("image/Obj/hint.png", "hint.png");
	return false;
}
bool hint::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size +5 };
	moveStop_checkdie_flag = die;

	return false;
}

void hint::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
}

void hint::Draw(void)
{

	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("R.png")[0], true);
	if (moveStop_checkdie_flag)
	{
		DrawExtendGraph(static_cast<int>(pos_.x),
			static_cast<int>(pos_.y - square_size*2 + 24 * sizeAdd_.y),
			static_cast<int>(pos_.x + square_size * 4.5 +24 - 24* sizeAdd_.x),
			static_cast<int>(pos_.y + square_size*0.5 ), lpImageMng.GetID("hint.png")[0], true);

		DrawGraph(static_cast<int>(pos_.x + square_size*0.5), static_cast<int>(pos_.y- square_size*1.5)+ 24 * sizeAdd_.y, lpImageMng.GetID(hintId_)[0], true);
	}


}