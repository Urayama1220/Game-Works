#include <DxLib.h>
#include "../common/imageMng.h"

#include "Simultaneousdoor.h"

Simultaneousdoor::Simultaneousdoor()
{
	Init();
}

Simultaneousdoor::Simultaneousdoor(double x, double y, bool die)
{
	Init(x, y, die);
}

Simultaneousdoor::~Simultaneousdoor()
{
}

bool Simultaneousdoor::Init()
{
	Obtype_ = objType::Simultaneousdoor;
	pos_ = { 0,0 };
	size_ = { square_size,square_size*2 };
	die_alive_Cnt = -1;
	moveStop_checkdie_flag = false;
	actionflag = false;
	lpImageMng.GetID("image/Obj/Door.png", "Door");
	OpendoorSE_ = LoadSoundMem("image/SE/open the door.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, OpendoorSE_);
	return false;
}



bool Simultaneousdoor::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,(y - 1) * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Simultaneousdoor::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	//listを使った初期化
	//トーチの数を数えている
	auto Oldcnt =0;
	if (die_alive_Cnt < 0)
	{
		die_alive_Cnt = 0;
		for (auto& obj : objList_)
		{
			if (obj->GetObjType() == objType::Simultaneous)
			{
				if (obj->moveStop_checkdie_flag)
				{
					continue;
				}
				//トーチの数だけプラス

				die_alive_Cnt++;
				Oldcnt = die_alive_Cnt;
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
	for (auto& obj : objList_)
	{
		if (obj->GetObjType() == objType::Simultaneous)
		{
			//死んでいた時
			if (obj->moveStop_checkdie_flag)
			{
				//カウントが０だったら
				if (die_alive_Cnt == 0)
				{
					moveStop_checkdie_flag = true;
				}
				else 
				{
					die_alive_Cnt = Oldcnt;
					moveStop_checkdie_flag = false;
				}
			}
		}
	}

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
	if (actionflag == false)
	{
		if (moveStop_checkdie_flag)
		{
			actionflag = true;
			pos_.x -= square_size;
			if (!CheckSoundMem(OpendoorSE_))
			{
				PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
			}
		}
	}
	else
	{
		if (moveStop_checkdie_flag == false)
		{
			pos_.x += square_size;
			actionflag = false;
			if (!CheckSoundMem(OpendoorSE_))
			{
				PlaySoundMem(OpendoorSE_, DX_PLAYTYPE_BACK, true);
			}
		}
	}
}

void Simultaneousdoor::Draw(void)
{
	DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Door")[0], true);
}