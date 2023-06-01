#include <DxLib.h>
#include "GameOverScene.h"
#include "../common/imageMng.h"
#include "Transition/FadeinOut.h"
#include "HalfwayScene.h"
#include "../Obj/Player.h"
#include "GameScene.h"
#include "SelectScene.h"
GameOverScene::GameOverScene()
{
	Choice_ = Stage::zero;
	Init();
	DrawOwnScreen();
}
GameOverScene::GameOverScene(Stage Choice, Stagelist& Slist, int RECnt, UniqueInput& imput, uniqueScene beforScene)
{
	ClearStagelist_ = std::move(Slist);
	/*Playerpos_ = Pos;*/
	ownScene_ = std::move(beforScene);
	imput_ = imput;
	Choice_ = Choice;
	
	RECnt_ = RECnt;
	//objList_ = objList;
	Init();
	DrawOwnScreen();
}

GameOverScene::~GameOverScene()
{
}

uniqueScene GameOverScene::Update(uniqueScene ownScene)
{
	/*if (startflag_)
	{
		if (CheckHitKey(KEY_INPUT_Z))
		{
			return std::make_unique<FadeinOut>(std::move(ownScene), std::make_unique<HalfwayScene>(Choice_, ClearStagelist_, RECnt_, imput_));
		}
	}*/

	imput_->Updata();
	auto& imputData = imput_->GetData(ImputType::NOW);
	auto& imputDataOld = imput_->GetData(ImputType::OLD);
	/*controller_->Updata();
	auto cntData = controller_->GetCntData();*/
	bool makeflag = false;
	
		if (pageCnt_ > 1)
		{
			if (imputData.count("左") && imputDataOld.count("左"))
			{
				if (imputData.at("左") && !imputDataOld.at("左"))
				{
					pageCnt_--;
					animOnCnt_ = 0;
					ChangeVolumeSoundMem(VolumeSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
				}
			}
		}
		if (pageCnt_ < pageCnt_Max_ - 1)
		{
			if (imputData.count("右") && imputDataOld.count("右"))
			{
				if (imputData.at("右") && !imputDataOld.at("右"))
				{
					pageCnt_++;
					animOnCnt_ = 0;
					ChangeVolumeSoundMem(VolumeSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					/*	selectionPos_++;*/
				}
			}
		}
		
		if (imputData.count("A") && imputDataOld.count("A"))
		{
			if (imputData.at("A") && !imputDataOld.at("A"))
			{
				ChangeVolumeSoundMem(VolumeSE, ecS_);
				PlaySoundMem(ecS_, DX_PLAYTYPE_BACK, true);


				makeflag = true;
			}

		}
		if (makeflag)
		{
			//次のシーンに移行
			TRACE("GameSceneに移行\n");
			/*uniqueScene game = std::make_unique<GameScene>(Choice_, ClearStagelist_);*/
			if (pageCnt_ ==1)
			{
				return std::make_unique<FadeinOut>(ownScene, std::make_unique<HalfwayScene>(Choice_, ClearStagelist_, RECnt_, imput_));
			}
			if (pageCnt_ == 2)
			{
				return std::make_unique<FadeinOut>(ownScene, std::make_unique<SelectScene>(Choice_, ClearStagelist_, imput_));
			}
			
			/*return std::make_unique<GameScene>(Choice_);*/
		}
		if (animOnCnt_ > 20)
		{
			animCnt_++;
		}
	/*if (animCnt_ / 10 % animCntmax <= 4)
	{
		animCnt_++;
	}
	else
	{
		startflag_ = true;
	}*/
	DrawOwnScreen();
	//GoalanimeCnt_++;
	animOnCnt_++;
	return ownScene;
}

void GameOverScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	ownScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	int miniSizeX = 30;
	int miniSizeY = 680;

	DrawExtendGraph(static_cast<int>(-miniSizeX),
		static_cast<int>(miniSizeY),
		static_cast<int>(screenSize_.x + miniSizeX),
		static_cast<int>(miniSizeY + ChipSize*2), lpImageMng.GetID("syber2mini.png")[0], true);
	int sizebut = 44;
	int butoffsetY = 65;
	int butoffsetX = 60;
	DrawGraph(screenSize_.x - butoffsetX * 2 - sizebut * 5, screenSize_.y - butoffsetY, lpImageMng.GetID("buttonZ.png")[/*alphaCnt_ / 30 % 2*/0], true);
	DrawGraph(screenSize_.x - butoffsetX * 2 - sizebut * 4, screenSize_.y - butoffsetY, lpImageMng.GetID("Decision.png")[0], true);
	int sizemove = 50;
	DrawGraph(butoffsetX * 2 + sizemove, screenSize_.y - butoffsetY, lpImageMng.GetID("leftbutton.png")[0], true);
	DrawGraph(butoffsetX * 2 + sizemove * 2, screenSize_.y - butoffsetY, lpImageMng.GetID("rightbutton.png")[0], true);
	DrawGraph(butoffsetX * 2 + sizemove * 3, screenSize_.y - butoffsetY, lpImageMng.GetID("move.png")[0], true);
	int oset = 250;
	int offsets = 5;
	int Changesize = 45;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150+ (animCnt_/2 %105) );
	if (pageCnt_ == 1)
	{
		DrawExtendGraph(oset - offsets * 2,
			screenSize_.y - oset - offsets,
			oset + Changesize * 4,
			screenSize_.y - oset + Changesize, lpImageMng.GetID("ant1.png")[0], true);
	}
	if (pageCnt_ == 2)
	{
		DrawExtendGraph(screenSize_.x - oset - Changesize * 4 - offsets * 2,
			screenSize_.y - oset - offsets,
			screenSize_.x - oset /*- 45 * 8*/ + offsets,
			screenSize_.y - oset + Changesize, lpImageMng.GetID("ant1.png")[0], true);//unnamed
	}
	int overOffset = 300;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

	DrawGraph(static_cast<int>(screenSize_.x/2 - overOffset),
			static_cast<int>(screenSize_.y/3), lpImageMng.GetID("gameover.png")[0], true);

	DrawGraph(static_cast<int>(oset),
		static_cast<int>(screenSize_.y - oset), lpImageMng.GetID("restart.png")[0], true);

	DrawGraph(static_cast<int>(screenSize_.x - oset - Changesize * 4),
		static_cast<int>(screenSize_.y - oset), lpImageMng.GetID("select.png")[0], true);


	
	if (animflag_)
	{
		/*DrawGraph(static_cast<int>(Playerpos_.x)* static_cast<int>(square_goresult_size) - 38,
			static_cast<int>(Playerpos_.y+ Offset_)* static_cast<int>(square_goresult_size) - 240 + 58,lpImageMng.GetID("warp_640.png")[animCnt_ / 10 % 5], true);*/
			/*for (auto pos : Poslist_)
			{
				DrawExtendGraph(static_cast<int>(pos.x * static_cast<int>(square_goresult_size) - 20),
					static_cast<int>(pos.y + Offset_) * static_cast<int>(square_goresult_size) - 80- UpMoveAnim_,
					static_cast<int>(pos.x) * static_cast<int>(square_goresult_size) + square_goresult_size - 1 + 10 + 20,
					static_cast<int>(pos.y + Offset_) * static_cast<int>(square_goresult_size) + square_goresult_size - 1+40- UpMoveAnim_,
					lpImageMng.GetID("warp_640.png")[animCnt_ % 26], true);
			}*/
		//DrawExtendGraph(static_cast<int>(Playerpos_.x * static_cast<int>(square_goresult_size) - AdjustmentSize_),
		//	static_cast<int>(Playerpos_.y + Offset_)* static_cast<int>(square_goresult_size) - (AdjustmentSize_ * 4) - UpMoveAnim_,
		//	static_cast<int>(Playerpos_.x)* static_cast<int>(square_goresult_size) + square_goresult_size - 1 + X_AdjustmentSize_ + AdjustmentSize_,
		//	static_cast<int>(Playerpos_.y + Offset_)* static_cast<int>(square_goresult_size) + square_goresult_size - 1 + (AdjustmentSize_ * 2) - UpMoveAnim_,
		//	lpImageMng.GetID("warp_640.png")[animCnt_ % animCntmax], true);
		////DrawGraph(0,0, lpImageMng.GetID("warp_6401.png")[0], true);
		//if (animCnt_ % animCntmax < Spawn_moveMaxCnt_)
		//{
		//	UpMoveAnim_ += 10;
		//}
	}
	else
	{
		/*DrawGraph(static_cast<int>(Playerpos_.x)* static_cast<int>(ChipSize),
			static_cast<int>(Playerpos_.y + Offset_)* static_cast<int>(ChipSize) - Spawn_moveCnt_, lpImageMng.GetID("Player.png")[0], true);*/
		/*for (auto pos : Poslist_)
		{
			DrawGraph(static_cast<int>(pos.x)* static_cast<int>(square_goresult_size),
				static_cast<int>(pos.y+ Offset_)* static_cast<int>(square_goresult_size) - Spawn_moveCnt, lpImageMng.GetID("SP.png")[0], true);
		}*/
		/*if (Spawn_moveCnt_ < Spawn_moveMaxCnt_)
		{
			Spawn_moveCnt_++;
		}
		else
		{
			animflag_ = true;
		}*/

	}
	//DrawExtendGraph(static_cast<int>(GoalEfPos_.x - GoaloffsetG), static_cast<int>(GoalEfPos_.y - ChipSize - GoaloffsetG), static_cast<int>(GoalEfPos_.x + ChipSize - 1 + GoaloffsetG), static_cast<int>(GoalEfPos_.y + ChipSize - 1 + GoaloffsetG), lpImageMng.GetID("Goal")[(GoalanimeCnt_ / 40) % 3 + 9], true);

	/*TRACE("%d\n", animCnt / 20 % animCntmax);*/
	//ownScene_->Draw();
	//afterScene_->Draw();
}

bool GameOverScene::Init(void)
{
	animCnt_ = 0;
	animOnCnt_ = 0;
	Spawn_moveCnt_ = 0;
	animflag_ = false;
	startflag_ = false;
	UpMoveAnim_ = 0;
	AdjustmentSize_ = 20;
	X_AdjustmentSize_ = 10;
	pageCnt_ = 1;
	pageCnt_Max_ = 3;

	ecSE = LoadSoundMem("image/SE/select.mp3");
	ecS_ = LoadSoundMem("image/SE/clicksele.mp3");

	int ecSE = LoadSoundMem("image/SE/down.mp3");
	ChangeVolumeSoundMem(VolumeObjSE, ecSE);
	PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
	/*for (auto objList_)
	{
	syber1mini
	}*/
	/*lpImageMng.GetID("image/Obj/Player.png", "Player.png", { 48,48 }, { 3,7 });
	lpImageMng.GetID("image/Obj/SP.png", "SP.png", { 48,48 }, { 3,5 });
	lpImageMng.GetID("image/start.png", "start.png", { 120,240 }, { 9,1 });
	lpImageMng.GetID("image/warp_640.png", "warp_640.png", { 640,480 }, { 2,13 });*/
	lpImageMng.GetID("image/logo/gameover.png", "gameover.png");
	lpImageMng.GetID("image/logo/select.png", "select.png");
	lpImageMng.GetID("image/logo/restart.png", "restart.png");
	lpImageMng.GetID("image/ant1.png", "ant1.png");
	//lpImageMng.GetID("image/warp_640.png", "warp_6401.png");
	/*rapidxml::file<>objFileName = "tmx/objList1.tsx";
	switch (Choice_)
	{
	case Stage::one:
		tmxObj_.LoadTMX("./tmx/map1.tmx");
		objFileName = "tmx/objList1.tsx";
		break;
	case Stage::two:
		tmxObj_.LoadTMX("./tmx/map2.tmx");
		objFileName = "tmx/objList2.tsx";
		break;
	case Stage::three:
		tmxObj_.LoadTMX("./tmx/map3.tmx");
		objFileName = "tmx/objList3.tsx";
		break;
	case Stage::four:
		tmxObj_.LoadTMX("./tmx/map4.tmx");
		objFileName = "tmx/objList4.tsx";
		break;
	case Stage::five:
		tmxObj_.LoadTMX("./tmx/map5.tmx");
		objFileName = "tmx/objList5.tsx";
		break;
	case Stage::six:
		tmxObj_.LoadTMX("./tmx/map6.tmx");
		objFileName = "tmx/objList6.tsx";
		break;
	case Stage::seven:
		tmxObj_.LoadTMX("./tmx/map7.tmx");
		objFileName = "tmx/objList7.tsx";
		break;
	case Stage::eight:
		tmxObj_.LoadTMX("./tmx/map8.tmx");
		objFileName = "tmx/objList8.tsx";
		break;
	case Stage::nine:
		tmxObj_.LoadTMX("./tmx/map9.tmx");
		objFileName = "tmx/objList9.tsx";
		break;
	case Stage::ten:
		tmxObj_.LoadTMX("./tmx/map10.tmx");
		objFileName = "tmx/objList10.tsx";
		break;
	case Stage::eleven:
		tmxObj_.LoadTMX("./tmx/map11.tmx");
		objFileName = "tmx/objList11.tsx";
		break;
	case Stage::twelve:
		tmxObj_.LoadTMX("./tmx/map12.tmx");
		objFileName = "tmx/objList12.tsx";
		break;
	case Stage::thirteen:
		tmxObj_.LoadTMX("./tmx/map13.tmx");
		objFileName = "tmx/objList13.tsx";
		break;
	case Stage::fourteen:
		tmxObj_.LoadTMX("./tmx/map14.tmx");
		objFileName = "tmx/objList14.tsx";
		break;
	case Stage::fifteen:
		tmxObj_.LoadTMX("./tmx/map15.tmx");
		objFileName = "tmx/objList15.tsx";
		break;
	default:
		break;
	}*/
	/*objctVec_ = objFileName.vecData();
	objctDoc.parse<0>(objctVec_.data());
	objctNode_ = objctDoc.first_node("objctList");
	auto node = objctNode_->first_node("objList");
	for (auto ListNode = node->first_node("List"); ListNode != nullptr; ListNode = ListNode->next_sibling())
	{
		std::string listname = ListNode->first_attribute("name")->value();
		auto objx = atof(ListNode->first_attribute("x")->value());
		auto objy = atof(ListNode->first_attribute("y")->value());
		if (listname == "Goal")
		{
			GoalPos_ = { objx * ChipSize ,(objy + 1) * ChipSize };
			GoalEfPos_ = { objx * ChipSize ,(objy + 1) * ChipSize };
		}
	}*/
	return false;
}