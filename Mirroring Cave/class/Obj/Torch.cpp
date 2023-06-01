#include <DxLib.h>
#include "Torch.h"
#include "../common/imageMng.h"
Torch::Torch()
{
	Init();
}

Torch::Torch(double x, double y, bool die)
{
	Init(x, y, die);
}

Torch::~Torch()
{
}

bool Torch::Init()
{
	Obtype_ = objType::Torch;
	pos_ = { 0,0 };
	animCnt_ = 0;
	size_ = { 24,square_size };
	die_alive_Cnt = 0;
	moveStop_checkdie_flag = false;
	minusflag_ = false;
	lpImageMng.GetID("image/Obj/Torch_F.png", "Torch_F", { 32,32 }, { 3,4 });
	lpImageMng.GetID("image/Obj/Torch_N.png", "Torch_N", { 32,32 }, { 3,4 });
	lpImageMng.GetID("image/Obj/TorchShadow2.png", "TorchShadow2.png");
	return false;
}

bool Torch::Init(double x, double y, bool die)
{
	Init();
	animCnt_ = static_cast<int>(x)* Calculated_value;
	pos_ = { x * square_size + (square_size / 4),y * square_size +5 };
	moveStop_checkdie_flag = die;

	return false;
}

void Torch::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{



	//死んだらカウントを減らす

	if (minusflag_ == false)
	{
		if (moveStop_checkdie_flag)
		{
			for (auto& obj : objList_)
			{
				if (obj->GetObjType() == objType::Door)
				{
					obj->die_alive_Cnt--;
				}
			}

			minusflag_ = true;
		}
	}
	else
	{
		if (moveStop_checkdie_flag == false)
		{
			for (auto& obj : objList_)
			{
				if (obj->GetObjType() == objType::Door)
				{
					obj->die_alive_Cnt++;
				}
			}

			minusflag_ = false;
		}
	}


	//死んだらカウントを減らす

	if (minusOPflag_ == false)
	{
		if (moveStop_checkdie_flag)
		{
			for (auto& obj : objList_)
			{
				if (obj->GetObjType() == objType::DoorOpen)
				{
					obj->die_alive_Cnt--;
				}
			}

			minusOPflag_ = true;
		}
	}
	else
	{
		if (moveStop_checkdie_flag == false)
		{
			for (auto& obj : objList_)
			{
				if (obj->GetObjType() == objType::DoorOpen)
				{
					obj->die_alive_Cnt++;
				}
			}
			minusOPflag_ = false;
		}
	}



	////トーチが復活したらドアを閉める
	//for (auto& obj : objList_)
	//{
	//	if (obj->GetObjType() == objType::Door)
	//	{
	//		if (moveStop_checkdie_flag == false)
	//		{
	//			obj->moveStop_checkdie_flag = false;
	//		}
	//	}
	//}
	animCnt_++;
}

void Torch::Draw(void)
{
	//TRACE("トーチ%d\n", moveStop_checkdie_flag);
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	if (moveStop_checkdie_flag == false)
	{
		DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / 7), lpImageMng.GetID("TorchShadow2.png")[0], true);
		DrawExtendGraph(static_cast<int>(pos_.x-10), static_cast<int>(pos_.y), static_cast<int>(pos_.x + size_.x-1+10), static_cast<int>(pos_.y + size_.y-1), lpImageMng.GetID("Torch_F")[(static_cast<UINT64>(animCnt_) / (Calculated_value * static_cast<int>(square_size)) % Calculated_value) + Calculated_value], true);
	}
	else
	{
		DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / 7), lpImageMng.GetID("TorchShadow2.png")[0], true);
		DrawExtendGraph(static_cast<int>(pos_.x-10), static_cast<int>(pos_.y), static_cast<int>(pos_.x + size_.x-1+10), static_cast<int>(pos_.y + size_.y-1), lpImageMng.GetID("Torch_N")[Calculated_value], true);

	}
}