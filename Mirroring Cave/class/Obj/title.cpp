#include <DxLib.h>
#include "../common/imageMng.h"

#include "title.h"

title::title()
{
	Init();
}

title::title(double x, double y, bool die)
{
	Init(x, y, die);
}

title::~title()
{
}

bool title::Init()
{
	pos_ = { 0,0 };
	size_ = { square_size,square_size*2 };
	die_alive_Cnt = -1;
	moveStop_checkdie_flag = false;
	objTitleCnt_ = 0;
	lpImageMng.GetID("image/Door.png", "Door");
	return false;
}

bool title::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,(y-1) * square_size };
	moveStop_checkdie_flag = die;
	OpenOldpos_ = 0;
	return false;
}

void title::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
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
	
}

void title::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, objTitleCnt_);
	DrawGraph(screenSize_.x / 4, screenSize_.y / 3, lpImageMng.GetID("titlelogo.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
}
