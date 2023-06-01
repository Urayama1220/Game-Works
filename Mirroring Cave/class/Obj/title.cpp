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
	//list���g����������
	//�g�[�`�̐��𐔂��Ă���
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
				//�g�[�`�̐������v���X
				
				die_alive_Cnt++;
			}
		}
	}
	//�g�[�`���Ȃ��Ȃ�����
	if (die_alive_Cnt == 0)
	{
		moveStop_checkdie_flag = true;
	}
	else
	{
		//�g�[�`������������h�A��߂�
	
		moveStop_checkdie_flag = false;

	}
	
}

void title::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, objTitleCnt_);
	DrawGraph(screenSize_.x / 4, screenSize_.y / 3, lpImageMng.GetID("titlelogo.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
}
