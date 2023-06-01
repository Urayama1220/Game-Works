#include <DxLib.h>
#include "Simultaneous.h"
#include "../common/imageMng.h"
Simultaneous::Simultaneous()
{
	Init();
}

Simultaneous::Simultaneous(double x, double y, bool die)
{
	Init(x, y, die);
}

Simultaneous::~Simultaneous()
{
}

bool Simultaneous::Init()
{
	Obtype_ = objType::Simultaneous;
	pos_ = { 0,0 };
	size_ = { 32,square_size };
	die_alive_Cnt = 0;
	moveStop_checkdie_flag = false;
	minusflag_ = false;
	lpImageMng.GetID("image/Obj/leverOff.png", "leverOff");
	lpImageMng.GetID("image/Obj/leverOn.png", "leverOn");
	return false;
}


bool Simultaneous::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size + (square_size / 5),y * square_size + 5 };
	moveStop_checkdie_flag = die;

	return false;
}

void Simultaneous::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	for (auto& obj : objList_)
	{
		if (obj->GetObjType() == objType::Simultaneousdoor)
		{
			//Ž€‚ñ‚¾‚çƒJƒEƒ“ƒg‚ðŒ¸‚ç‚·

			if (minusflag_ == false)
			{
				if (moveStop_checkdie_flag)
				{
					obj->die_alive_Cnt--;

					minusflag_ = true;
				}
			}
			else
			{
				if (moveStop_checkdie_flag == false)
				{
					obj->die_alive_Cnt++;
					minusflag_ = false;
				}
			}
		}
	}
}

void Simultaneous::Draw(void)
{
	if (moveStop_checkdie_flag == false)
	{
		DrawGraph(static_cast<int>(pos_.x - 10), static_cast<int>(pos_.y), lpImageMng.GetID("leverOff")[0], true);
		//DrawExtendGraph(static_cast<int>(pos_.x - 10), static_cast<int>(pos_.y), static_cast<int>(pos_.x + size_.x - 1 + 10), static_cast<int>(pos_.y + size_.y - 1), lpImageMng.GetID("leverOff")[0], true);
	}
	else
	{
		//DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / 7), lpImageMng.GetID("TorchShadow2.png")[0], true);
		/*DrawExtendGraph(static_cast<int>(pos_.x - 10), static_cast<int>(pos_.y), static_cast<int>(pos_.x + size_.x - 1 + 10), static_cast<int>(pos_.y + size_.y - 1), lpImageMng.GetID("leverOff")[0], true);*/
		DrawGraph(static_cast<int>(pos_.x - 10), static_cast<int>(pos_.y), lpImageMng.GetID("leverOn")[0], true);

	}
}
