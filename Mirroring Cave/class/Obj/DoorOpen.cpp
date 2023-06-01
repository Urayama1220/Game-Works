#include <DxLib.h>
#include "../common/imageMng.h"

#include "DoorOpen.h"

DoorOpen::DoorOpen()
{
	Init();
}

DoorOpen::DoorOpen(double x, double y, bool die)
{
	Init(x, y, die);
}

DoorOpen::~DoorOpen()
{
}

bool DoorOpen::Init()
{
	Obtype_ = objType::DoorOpen;
	pos_ = {0,0};
	size_ = { square_size,square_size*2 };
	die_alive_Cnt = -1;
	die_alive_CntMax_ = 0;
	moveStop_checkdie_flag = false;
	actionflag_ = false;
	OpendoorSE_ = LoadSoundMem("image/SE/open the door.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, OpendoorSE_);
	lpImageMng.GetID("image/Obj/OpenDoor.png", "OpenDoor");
	return false;
}

bool DoorOpen::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,(y - 1) * square_size };
	OriginalPos_ = pos_;
	moveStop_checkdie_flag = die;
	OpenOldpos_ = 0;
	CloseOldpos_ = 0;
	return false;
}

void DoorOpen::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
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
				die_alive_CntMax_++;
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

	//トーチが復活したらドアを閉める
	if (die_alive_Cnt == die_alive_CntMax_)
	{
		moveStop_checkdie_flag = true;
	}
	else
	{
		//トーチがなくなったら
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
		/*if (pos_.x - square_size < pos_.x)
		{
			pos_.x = Move_slowlyCnt;
		}*/
	}
	else
	{
		if (OpenOldpos_ - square_size <= pos_.x)
		{
			pos_.x -= Move_slowlyCnt;
			//上下に揺らしたい時間があるときに
			/*pos_.y += ;*/
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
	//TRACE("%f\n", pos_.x);
}

void DoorOpen::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("OpenDoor")[0], true);
}
