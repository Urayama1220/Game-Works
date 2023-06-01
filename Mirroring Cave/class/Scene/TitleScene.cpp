#include <DxLib.h>
#include "../common/imageMng.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "../Input/imput_Scene/keyboard.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#include "../Obj/Player.h"
#include "../Obj/Supporter.h"
#include "../Obj/Torch.h"
TitleScene::TitleScene(UniqueInput& imput)
{
	imput_ = std::move(imput);
	Init();
	DrawOwnScreen();
}

TitleScene::~TitleScene()
{
}

uniqueScene TitleScene::Update( uniqueScene ownScene)
{
	imput_->Updata();
	auto& imputData = imput_->GetData(ImputType::NOW);
	auto& imputDataOld = imput_->GetData(ImputType::OLD);
	if (imputData.count("A") && imputDataOld.count("A"))
	{
		if (imputData.at("A") /*&& !imputDataOld.at("A")*/)
		{
			Timecnt_++;
			objTitlestartCnt_ = objTitlestartCnt_Max_;
			objTitleCnt_ = objTitleCnt_Max_;
			
		}
		else
		{
			Timecnt_ = 0;
		}
	}
	if (Timecnt_ > Timecnt_SE_Max_)
	{
		if (!CheckSoundMem(ecSE_))
		{
			ChangeVolumeSoundMem(VolumeSE, ecSE_);
			PlaySoundMem(ecSE_, DX_PLAYTYPE_BACK, true);
			
		}
	}
	if (Timecnt_ > Timecnt_Max_)
	{
		//次のシーンに移行
		TRACE("セレクトシーンに移行\n");
		return std::make_unique<SelectScene>(imput_);
	}
	if (titleflameCnt_ > 120)
	{
		title1 = true;
	}
	if (titleflameCnt_ > 150)
	{
		title2 = true;
	}
	if (titleflameCnt_ > 180)
	{
		title3 = true;
	}
	if (titleflameCnt_ > 210)
	{
		title4 = true;
	}
	titleflameCnt_++;

	
	for (auto& obj : objTitleList_)
	{
		obj->Updata(tmxObj_, objTitleList_, Installation_offset);
		if (obj->GetObjType() == objType::Torch)
		{
			obj->Updata(tmxObj_, objTitleList_);
		}
	}
	//キャラが後ろにいったらタイトルが出るように
	if (objTitlestartCnt_ > starttitle_)
	{
		
		objTitleCnt_ += 2;
	}
	if (objTitleCnt_ > objTitleCnt_Max_)
	{
		if (titleInmove_ < 20)
		{
			titleInmove_++;
		}
	}
	objTitlestartCnt_++;
	//TRACE("%d\n", Timecnt_);
	DrawOwnScreen();
	return ownScene;
}

void TitleScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawExtendGraph(0, 0, static_cast<int>(screenSize_.x - 1), static_cast<int>(screenSize_.y - 1), lpImageMng.GetID("background")[0], true);
	auto TileSize = tmxObj_.GetTileSize();
	for (const auto& layer : tmxObj_.GetMapData())
	{
		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
		{
			for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
			{
				if (0 < y * tmxObj_.GetWorldArea().x + x && static_cast<UINT64>(y) * tmxObj_.GetWorldArea().x + static_cast<UINT64>(x) < layer.second.size())
				{
					//int gid = tmxObj_.GetMapData(layer.first, x - tmxObj_.GetFirstgID(), y);
					int gid = layer.second[static_cast<UINT64>(y) * tmxObj_.GetWorldArea().x + static_cast<UINT64>(x)] - tmxObj_.GetFirstgID();
					if (gid >= 0)
					{
						DrawGraph(x * TileSize.x, y * TileSize.y + (Offset_ * ChipSize), lpImageMng.GetID("tiles1.png")[gid], true);
					}
				}
			}

		}
	}
	for (auto& obj : objTitleList_)
	{
		obj->Draw();
	}
	if (objTitleCnt_ > objTitleCnt_Max_)
	{
		
		int InMoveoffset_ = 20;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100+ titleInmove_*7);
		DrawGraph(screenSize_.x / 3, screenSize_.y / 1.5+ InMoveoffset_ - titleInmove_, lpImageMng.GetID("LongPush.png")[Timecnt_ %20], true);
		DrawGraph(screenSize_.x / 3, screenSize_.y / 1.5 + InMoveoffset_- titleInmove_, lpImageMng.GetID("buttonZ.png")[Timecnt_ / 10 % 2], true);
		DrawGraph(screenSize_.x / 2.5, screenSize_.y / 1.5 + InMoveoffset_- titleInmove_, lpImageMng.GetID("Zbuttonpush.png")[objTitleCnt_ / 20 % 2], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	}
	int  Halfsize = 350;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,  objTitleCnt_);
	DrawGraph(screenSize_.x / 2 - Halfsize, screenSize_.y / 4+21, lpImageMng.GetID("titlelogo.png")[0], true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - objTitleCnt_+21);
	if (title1)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 135 +  titleflameCnt_);
		DrawGraph(screenSize_.x / 2 - Halfsize, screenSize_.y / 3, lpImageMng.GetID("titlelogo1.png")[0], true);
	}
	if (title2)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA,  105 +  titleflameCnt_);
		DrawGraph(screenSize_.x / 2 - Halfsize + LogoSplitSize_.x, screenSize_.y / 3, lpImageMng.GetID("titlelogo2.png")[0], true);
	}
	if (title3)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75 + titleflameCnt_);
		DrawGraph(screenSize_.x / 2 - Halfsize + LogoSplitSize_.x * 2, screenSize_.y / 3, lpImageMng.GetID("titlelogo3.png")[0], true);
	}
	if (title4)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 40 + titleflameCnt_);
		DrawGraph(screenSize_.x / 2 - Halfsize + LogoSplitSize_.x * 3, screenSize_.y / 3, lpImageMng.GetID("titlelogo4.png")[0], true);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	//フォー分でまとめてみる
}

bool TitleScene::Init(void)
{
	objTitleCnt_ = 0;
	objTitlestartCnt_Max_ = 600;
	objTitleCnt_Max_ = 170;
	Timecnt_SE_Max_ = 19;
	Timecnt_Max_ = 20;
	starttitle_ = 200;
	LogoSplitSize_ = { 148,192 };
	//LogoLastSize_ = { 242,192 };
	titleflameCnt_ = 0;
	Timecnt_ = 0;
	title1 = false;
	title2 = false;
	title3 = false;
	title4 = false;
	titleInmove_ = 0;
	lpImageMng.GetID("image/2346367.jpg", "background");
	lpImageMng.GetID("image/buttonZ.png", "buttonZ.png", { 50,50 }, { 2,1 });
	lpImageMng.GetID("image/logo/Zbuttonpush.png", "Zbuttonpush.png",{288,48}, {2,1});
	lpImageMng.GetID("image/logo/titlelogo2.png", "titlelogo.png");
	lpImageMng.GetID("image/logo/fremfont1.png", "titlelogo0.png",LogoSplitSize_, { 4,1 });
	lpImageMng.GetID("image/logo/fremfont1.png", "titlelogo1.png");
	lpImageMng.GetID("image/logo/fremfont2.png", "titlelogo2.png");
	lpImageMng.GetID("image/logo/fremfont3.png", "titlelogo3.png");
	lpImageMng.GetID("image/logo/fremfont4.png", "titlelogo4.png");


	lpImageMng.GetID("image/LongPush1.png", "LongPush.png", {50,50}, {21,1});
	objTitleList_.emplace_back(std::make_unique<Torch>(4, 13, false));
	objTitleList_.emplace_back(std::make_unique<Torch>(8, 13, true));
	objTitleList_.emplace_back(std::make_unique<Torch>(12, 13, false));
	objTitleList_.emplace_back(std::make_unique<Torch>(16, 13, true));
	objTitleList_.emplace_back(std::make_unique<Supporter>(-2, 14, false));
	objTitleList_.emplace_back(std::make_unique<Player>(-10, 14, false));
	tmxObj_.LoadTMX("./tmx/titlemap.tmx");
	ecSE_ = LoadSoundMem("image/SE/titleclick.mp3");

	return true;
}
