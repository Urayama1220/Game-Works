#include <DxLib.h>
#include "../common/imageMng.h"
#include "Respawn.h"
Respawn::Respawn()
{
	Init();
}
Respawn::Respawn(double x, double y, bool die)
{
	Init(x,y, die);
}
Respawn::~Respawn()
{
}

bool Respawn::Init()
{
	Obtype_ = objType::Respawn;
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//仮サイズ
	moveStop_checkdie_flag = false;
	lpImageMng.GetID("image/Obj/Re.png", "Re");
	return false;
}
bool Respawn::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Respawn::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	//if (CheckHitKey(KEY_INPUT_R))
	//{
	//	for (auto& obj : objList_)
	//	{
	//		if (obj->pos_ == pos_)
	//		{
	//			continue;
	//		}
	//		//それっぽい機能（実際には使わない）
	//		if (obj->GetObjType() == objType::Player)
	//		{
	//			obj->pos_ = pos_;
	//			ReCnt_++;
	//			TRACE("%d\n", ReCnt_);
	//		}
	//	}
	//}
}

void Respawn::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	//DrawFormatString(1000, 10, 0xffffff, "%d\n", ReCnt_);
	DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Re")[0], true);

}