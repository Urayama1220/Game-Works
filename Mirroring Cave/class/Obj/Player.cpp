
#include <DxLib.h>
#include <cmath>  
#include<sstream>
#include "../Input/KeyInput.h"
#include "../common/imageMng.h"

#include "Player.h"
#include "Checkmove.h"
#include "Collide.h"
//#include "../../_debug/_DebugConOut.h"
Player::Player()
{
	Init();
}
Player::Player(double x, double y, bool die)
{
	Init(x, y, die);

}
Player::Player(double x ,double y, bool die, ObjUlist& list)
{
	HintList_ = std::move(list);
	Init(x,y, die);
	
}

Player::~Player()
{
	
}

bool Player::Init()
{
	Obtype_ = objType::Player;
	controller_ = std::make_unique<KeyInput>();
	pos_ = {0,0 };
	size_ = { square_size,square_size };//仮サイズ
	moveStop_checkdie_flag = false;
	lpAnimMng.LoadAnim("tmx/anim.tsx");
	animItrCnt_ = std::move(lpAnimMng.SetAnimData("Player", "run"));
	rapidxml::file<> moduleFileName = "tmx/action.tsx";
	stateVec_ = moduleFileName.vecData();
	stateDoc.parse<0>(stateVec_.data());
	stateNode_ = stateDoc.first_node("moduleList");

	rapidxml::file<> moduleTitleFileName = "tmx/actiontitle.tsx";
	TitlestateVec_ = moduleTitleFileName.vecData();
	TitlestateDoc.parse<0>(TitlestateVec_.data());
	TitlestateNode_ = TitlestateDoc.first_node("moduleList");

	RoadSE_ = LoadSoundMem("image/SE/Footsteps03-1L.mp3");
	lpImageMng.GetID("image/Obj/Shadow.png", "Shadow.png");
	CheckTitleHit_ = false;
	TitleHitCnt_ = 0;
	ChangeVolumeSoundMem(VolumeObjSE - 50, RoadSE_);
	return false;
}

bool Player::Init(double x, double y, bool die)
{
	Init();
	pos_ = { x * square_size,y * square_size };
	moveStop_checkdie_flag = die;

	return false;
}

void Player::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
	//TRACE("%d\n", dir_);
	if (moveStop_checkdie_flag)
	{
		
		GameOverMove_flag = true;
	}
	if (!controller_)
	{
		return;
	}
	controller_->Updata();
	auto cntData = controller_->GetCntData();

	if (!moveStop_checkdie_flag)
	{
		//オブジェクト同士の当たり判定
		
		controller_ = std::move(Collide()(pos_, size_, objList_, std::move(controller_), moveStop_checkdie_flag));

		//マップとプレイヤーの当たり判定とアニメーション
		for (auto node = stateNode_->first_node("actNode"); node != nullptr; node = node->next_sibling())
		{
			//オブジェクト同士の判定に当たった際の動作が書いてある
 			ModuleNode()(this, node, tmxObj_, objList_);
		}
		if (!HintList_.empty())
		{
			PlayerhintHit()(pos_, size_, HintList_);
		}
		/*CorrectPos()(pos_, size_);*/
	}
	PlaySE();
	lpAnimMng.UpdataAnime(animItrCnt_);
	for (const auto& hint : HintList_)
	{
		hint->Updata(tmxObj_, objList_);
	}
	
}
//タイトル用アップデート
void Player::Updata(TmxObj& tmxObj_, ObjUlist& objList_, double offset)
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


		//マップとプレイヤーの当たり判定とアニメーション
		pos_.y = pos_.y - offset;
		for (auto node = TitlestateNode_->first_node("actNode"); node != nullptr; node = node->next_sibling())
		{
			//オブジェクト同士の判定に当たった際の動作が書いてある
			ModuleNode()(this, node, tmxObj_, objList_);
		}
		pos_.y = pos_.y + offset;
		/*controller_ = std::move(Collide()(pos_, size_, objList_, std::move(controller_)));*/
		if (CheckTitleHit_)
		{
			TitleHitCnt_++;
			if (TitleHitCnt_ > 20)
			{
				CheckTitleHit_ = false;
				TitleHitCnt_ = 0;
			}
		}
	}
	PlaySE();
	lpAnimMng.UpdataAnime(animItrCnt_);

	
}

void Player::Draw(void)
{
	/*DrawBox(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(pos_.x) + static_cast<int>(size_.x),
		static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
	/*DrawGraph(pos_.x, pos_.y,lpImageMng.GetID("krokro.png")[(*animItrCnt_.animitr)[GraphHD]],true);*/
	for (const auto& hint : HintList_)
	{
		hint->Draw();
	}
	if (moveLR == DIR_LR::L)
	{
		DrawGraph(static_cast<int>(pos_.x+size_.x/3.5), static_cast<int>(pos_.y+size_.y - size_.x/ ShadowSize- Objoffset), lpImageMng.GetID("Shadow.png")[0], true);
		DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y- Objoffset), lpImageMng.GetID("Player.png")[(*animItrCnt_.animitr)[GraphHD]], true);
	}
	else
	{
		DrawGraph(static_cast<int>(pos_.x + size_.x / 3.5), static_cast<int>(pos_.y + size_.y - size_.x / ShadowSize- Objoffset), lpImageMng.GetID("Shadow.png")[0], true);
		DrawTurnGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y- Objoffset), lpImageMng.GetID("Player.png")[(*animItrCnt_.animitr)[GraphHD]], true);
	}

}
void Player::PlaySE()
{
	controller_->Updata();
	auto cntData = controller_->GetCntData();
	if (cntData[InputID::Left][static_cast<int>(Trg::Now)] ||
		cntData[InputID::Right][static_cast<int>(Trg::Now)] ||
		cntData[InputID::Down][static_cast<int>(Trg::Now)] ||
		cntData[InputID::Up][static_cast<int>(Trg::Now)])
	{
		if (!CheckSoundMem(RoadSE_))
		{

			PlaySoundMem(RoadSE_, DX_PLAYTYPE_BACK, true);
		}
	}
	else
	{
		StopSoundMem(RoadSE_);

	}
}