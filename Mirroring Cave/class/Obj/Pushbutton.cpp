
#include <DxLib.h>
#include "../common//imageMng.h"
#include "Pushbutton.h"
Pushbutton::Pushbutton()
{
	Init();
}
Pushbutton::Pushbutton(double x, double y, bool die)
{
	Init(x, y, die);
}
Pushbutton::~Pushbutton()
{
}

bool Pushbutton::Init()
{
	Obtype_ = objType::Pushbutton;
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//âºÉTÉCÉY
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/Pushbutton.png", "Pushbutton");
	lpImageMng.GetID("image/Obj/Pushbutton2.png", "Pushbutton2");
	return false;
}



bool Pushbutton::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Pushbutton::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	/*if (!moveStop_checkdie_flag)
	{
		if (CollideH()(pos_, size_, objList_, tmxObj_))
		{
			moveStop_checkdie_flag = true;
		}
	}*/
}

void Pushbutton::Draw(void)
{
	if (!moveStop_checkdie_flag)
	{
		DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Pushbutton")[0], true);
	}
	else
	{
		DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Pushbutton2")[0], true);
	}

}