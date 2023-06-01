#include <DxLib.h>
#include "../common/imageMng.h"
#include "PushDoor.h"

PushDoor::PushDoor()
{
	Init();
}

PushDoor::PushDoor(double x, double y, bool die)
{
	Init(x, y, die);
}

PushDoor::~PushDoor()
{
}

bool PushDoor::Init()
{
	Obtype_ = objType::DoorOpen;
	pos_ = { 0,0 };
	size_ = { square_size,square_size*2 };
	OpenOldpos_ = 0;
	CloseOldpos_ = 0;
	moveStop_checkdie_flag = false;
	actionflag_ = false;
	OpendoorSE_ = LoadSoundMem("image/SE/open the door.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, OpendoorSE_);
	lpImageMng.GetID("image/Obj/Door.png", "Door");
	 ecSE = LoadSoundMem("image/SE/gamePush.mp3");

	return false;
}


bool PushDoor::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,(y - 1) * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void PushDoor::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	/*for (auto& obj : objList_)
	{
		if (obj->GetObjType() == objType::Pushbutton)
		{
			if (obj->moveStop_checkdie_flag)
			{
				moveStop_checkdie_flag = true;
			}
			else
			{
				moveStop_checkdie_flag = false;
			}

		}
	}*/

	////動作 フラグがたったら、ブロックをずらす
	//if (actionflag_ == false)
	//{
	//	if (moveStop_checkdie_flag)
	//	{
	//		actionflag_ = true;
	//		pos_.x -= square_size;
	//		if (!CheckSoundMem(OpendoorSE_))
	//		{
	//			PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
	//		}

	//		ChangeVolumeSoundMem(VolumeObjSE -30, ecSE);
	//		PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
	//	}
	//}
	//else
	//{
	//	if (moveStop_checkdie_flag == false)
	//	{
	//		pos_.x += square_size;
	//		actionflag_ = false;
	//		if (!CheckSoundMem(OpendoorSE_))
	//		{
	//			PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
	//		}
	//	}
	//}
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

}

void PushDoor::Draw(void)
{
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Door")[0], true);
}
