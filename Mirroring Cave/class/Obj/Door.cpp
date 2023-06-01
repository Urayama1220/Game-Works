#include <DxLib.h>
#include "../common/imageMng.h"

#include "Door.h"

Door::Door()
{
	Init();
}

Door::Door(double x, double y, bool die)
{
	Init(x, y, die);
}

Door::~Door()
{
}

bool Door::Init()
{
	Obtype_ = objType::Door;
	pos_ = { 0,0 };
	size_ = { square_size,square_size*2 };
	die_alive_Cnt = -1;
	moveStop_checkdie_flag = false;
	actionflag_ = false;
	lpImageMng.GetID("image/Obj/Door.png", "Door");
	OpendoorSE_ = LoadSoundMem("image/SE/open the door.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, OpendoorSE_);
	return false;
}

bool Door::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,(y-1) * square_size };
	moveStop_checkdie_flag = die;
	OpenOldpos_ = 0;
	CloseOldpos_ = 0;
	return false;
}

void Door::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	//listを使った初期化
	//トーチの数を数えている
	if (die_alive_Cnt < 0)
	{
		die_alive_Cnt = 0;
		for (auto& obj : objList_)
		{
			if (obj->GetObjType() == objType::Torch)
			{
				if (obj->moveStop_checkdie_flag)
				{
					continue;
				}
				//トーチの数だけプラス
				
				die_alive_Cnt++;
			}
		}
	}
	//for (auto& obj : objList_)
	//{
	//	if (obj->GetObjType() == objType::Torch)
	//	{
	//		//死んだらカウントを減らす


	//		if (obj->moveStop_checkdie_flag)
	//		{
	//			die_alive_Cnt--;
	//		}

	//		if (obj->moveStop_checkdie_flag == false)
	//		{
	//			die_alive_Cnt++;
	//		}

	//	}
	//}
	//トーチがなくなったら
	if (die_alive_Cnt == 0)
	{
		moveStop_checkdie_flag = true;
	}
	else
	{
		//トーチが復活したらドアを閉める
	
		moveStop_checkdie_flag = false;

	}
	//動作 フラグがたったら、ブロックをずらす
	if (actionflag_ == false)
	{
		if (CloseOldpos_ + square_size >= pos_.x)
		{
			pos_.x += Move_slowlyCnt;
		}
		else
		{
			if (moveStop_checkdie_flag)
			{
				actionflag_ = true;
				/*pos_.x -= square_size;*/
				if (!CheckSoundMem(OpendoorSE_))
				{
					PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
				}
				OpenOldpos_ = pos_.x;
			}
		}
		
	}
	else
	{
		if (OpenOldpos_ - square_size <= pos_.x)
		{
			pos_.x -= Move_slowlyCnt;
		}
		else
		{
			if (moveStop_checkdie_flag == false)
			{
				/*pos_.x += square_size;*/
				actionflag_ = false;
				if (!CheckSoundMem(OpendoorSE_))
				{
					PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
				}
				CloseOldpos_ = pos_.x;
			}
		}
	}
	/*TRACE("%f:%f\n", pos_.x - square_size,pos_.x);*/
}

void Door::Draw(void)
{
	
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Door")[0], true);
}
