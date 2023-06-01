#include <DxLib.h>
#include "TorchOpen.h"
#include "../common/imageMng.h"
TorchOpen::TorchOpen()
{
}

TorchOpen::TorchOpen(double x, double y)
{
	Init(x, y);
}

TorchOpen::~TorchOpen()
{
}

bool TorchOpen::Init(double x, double y)
{
	Obtype_ = objType::Torch;
	pos_ = { x * square_size+ (square_size/4),y * square_size+5 };
	animCnt_ = x* Calculated_value;
	size_ = { 32,square_size };
	die_alive_Cnt = 0;
	moveStop_checkdie_flag = false;
	minusflag_ = false;
	lpImageMng.GetID("image/Torch_F.png", "Torch_F", { 32,32 }, { 3,4 });
	lpImageMng.GetID("image/Torch_N.png", "Torch_N", { 32,32 }, { 3,4 });

	return false;
}

void TorchOpen::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	
	
	for (auto& obj : objList_)
	{
		if (obj->GetObjType() == objType::DoorOpen)
		{
			//���񂾂�J�E���g�����炷

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

	////�g�[�`������������h�A��߂�
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

void TorchOpen::Draw(void)
{
	//TRACE("�g�[�`%d\n", moveStop_checkdie_flag);
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	if (moveStop_checkdie_flag == false)
	{
		DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Torch_N")[Calculated_value], true);
	}
	else
	{
		
		DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Torch_F")[(animCnt_ / (Calculated_value * static_cast<int>(square_size)) % Calculated_value) + Calculated_value], true);

	}
}