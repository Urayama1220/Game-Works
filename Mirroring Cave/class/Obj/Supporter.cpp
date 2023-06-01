#include <DxLib.h>
#include <cmath>  
#include<sstream>
#include "../common/imageMng.h"
#include "../Input/KeyInput.h"

#include "Supporter.h"

#include "CheckmoveSP.h"
#include "Collide.h"
Supporter::Supporter()
{
	Init();
}

Supporter::Supporter(double x, double y, bool die)
{
	Init(x,y, die);
}

Supporter::~Supporter()
{
}

bool Supporter::Init()
{
	Obtype_ = objType::Supporter;
	controller_ = std::make_unique<KeyInput>();
	pos_ = { 0,0 };
	size_ = { square_size,square_size };//仮サイズ
	moveStop_checkdie_flag = false;
	lpAnimMng.LoadAnim("tmx/animSP.tsx");
	animItrCnt_ = std::move(lpAnimMng.SetAnimData("Supporter", "run"));
	rapidxml::file<> moduleFileName = "tmx/actionSP.tsx";
	stateVec_ = moduleFileName.vecData();
	stateDoc.parse<0>(stateVec_.data());
	stateNode_ = stateDoc.first_node("moduleList");

	rapidxml::file<> moduleTitleFileName = "tmx/actiontitleSP.tsx";
	TitlestateVec_ = moduleTitleFileName.vecData();
	TitlestateDoc.parse<0>(TitlestateVec_.data());
	TitlestateNode_ = TitlestateDoc.first_node("moduleList");

	CheckTitleHitSP_ = false;
	TitleHitCntSP_ = 0;
	BoxSE_ = LoadSoundMem("image/SE/box.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, BoxSE_);
	lpImageMng.GetID("image/Obj/Shadow.png", "Shadow.png");
	SE_ = false;
	return false;
}


bool Supporter::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Supporter::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	if (!controller_)
	{
		return;
	}
		controller_->Updata();
		auto cntData = controller_->GetCntData();
		if (!moveStop_checkdie_flag)
		{
			//オブジェクト同士の当たり判定
			/*CollideS()(pos_, size_, objList_, tmxObj_, raycast_);*/
			//マップとサポーターの当たり判定とアニメーション
			for (auto node = stateNode_->first_node("actNode"); node != nullptr; node = node->next_sibling())
			{
				//オブジェクト同士の判定に当たった際の動作が書いてある
				ModuleNodeSP()(this, node, tmxObj_, objList_);
				
			}
			controller_ = std::move(CollideS()(pos_, size_, objList_, std::move(controller_), moveStop_checkdie_flag));
		}
		else
		{
			if (!SE_)
			{
				if (!CheckSoundMem(BoxSE_))
				{
					SE_ = true;
					PlaySoundMem(BoxSE_, DX_PLAYTYPE_BACK, true);
				}
			}
			animItrCnt_ = lpAnimMng.SetAnimData(animItrCnt_.ObjID, "Hole");//state

		}
}

void Supporter::Updata(TmxObj& tmxObj_, ObjUlist& objList_, double offset)
{
	if (!controller_)
	{
		return;
	}
	controller_->Updata();
	auto cntData = controller_->GetCntData();
	if (!moveStop_checkdie_flag)
	{
		pos_.y = pos_.y - offset;
		for (auto node = TitlestateNode_->first_node("actNode"); node != nullptr; node = node->next_sibling())
		{
			//オブジェクト同士の判定に当たった際の動作が書いてある
			ModuleNodeSP()(this, node, tmxObj_, objList_);

		}
		pos_.y = pos_.y + offset;
		if (CheckTitleHitSP_)
		{
			TitleHitCntSP_++;
			if (TitleHitCntSP_ > 20)
			{
				CheckTitleHitSP_ = false;
				TitleHitCntSP_ = 0;
			}
		}
	}
	else
	{
		if (!SE_)
		{
			if (!CheckSoundMem(BoxSE_))
			{
				SE_ = true;
				PlaySoundMem(BoxSE_, DX_PLAYTYPE_BACK, true);
			}
		}
		animItrCnt_ = lpAnimMng.SetAnimData(animItrCnt_.ObjID, "Hole");//state

	}
}

void Supporter::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	/*DrawGraph(pos_.x, pos_.y, lpImageMng.GetID("SP.png")[(*animItrCnt_.animitr)[GraphHD]], true);*/
	
	if (!moveStop_checkdie_flag)
	{
		if (moveLR == DIR_LR::L)
		{
			DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / 7- Objoffset), lpImageMng.GetID("Shadow.png")[0], true);
			DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y- Objoffset), lpImageMng.GetID("SP.png")[(*animItrCnt_.animitr)[GraphHD]], true);
		}
		else
		{
			DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / 7- Objoffset), lpImageMng.GetID("Shadow.png")[0], true);
			DrawTurnGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y- Objoffset), lpImageMng.GetID("SP.png")[(*animItrCnt_.animitr)[GraphHD]], true);
		}
	}
	else
	{
		if (moveLR == DIR_LR::L)
		{
			DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("SP.png")[(*animItrCnt_.animitr)[GraphHD]], true);
		}
		else
		{
			DrawTurnGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("SP.png")[(*animItrCnt_.animitr)[GraphHD]], true);
		}
	}

	
}