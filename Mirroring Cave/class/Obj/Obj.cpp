#include <DxLib.h>
#include "../common/imageMng.h"
#include "../Input/KeyInput.h"
#include "Obj.h"
Obj::Obj()
{
	Obtype_ = objType::Max;
	moveLR = DIR_LR::MAX;
	moveStop_checkdie_flag = false;
	speed_ = 0;
	die_alive_Cnt = -1;
	GameOverMove_flag = false;
	Moveabledir = MOVE_DIRECTION::MAX;
}

Obj::~Obj()
{
}

void Obj::Draw(void)
{
	/*DrawGraph(pos_.x, pos_.y, lpImageMng.GetID("gfx.png")[0], true);*/
	/*DrawBox(pos_.x, pos_.y, pos_.x + 50, pos_.y + 50, 0xff00ff,true);*/
}

