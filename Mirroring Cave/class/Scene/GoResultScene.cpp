#include <DxLib.h>
#include "GoResultScene.h"
#include "ResultScene.h"
#include "../common/imageMng.h"
#include "Transition/FadeinOut.h"

#include "../Obj/Player.h"
#include "../Obj/Supporter.h"
#include "../Obj/Goal.h"
GoResultScene::GoResultScene()
{
	Choice_ = Stage::zero;
	Init();
	DrawOwnScreen();
}
GoResultScene::GoResultScene(Stage Choice, Stagelist& Slist ,int time, int RECnt, UniqueInput& imput, Vector2Dbl Pos)
{
	ClearStagelist_ = std::move(Slist);
	Playerpos_ = Pos;
	imput_ = imput;
	Choice_ = Choice;
	aftime = time;
	RECnt_ = RECnt;
	//objList_ = objList;
	Init();
	DrawOwnScreen();
}

GoResultScene::~GoResultScene()
{
}

uniqueScene GoResultScene::Update(uniqueScene ownScene)
{
	if (startflag_)
	{
		return std::make_unique<FadeinOut>(std::move(ownScene),std::make_unique<ResultScene>(Choice_, ClearStagelist_, aftime, RECnt_, imput_));
	}
	if (animCnt_ / 10 % animCntmax <= 4)
	{
		animCnt_++;
	}
	else
	{
		startflag_ = true;
	}
	DrawOwnScreen();
	GoalanimeCnt_++;
	return ownScene;
}

void GoResultScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto TileSize = tmxObj_.GetTileSize();
	for (const auto& layer : tmxObj_.GetMapData())
	{
		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
		{
			for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
			{
				if (0 < y * tmxObj_.GetWorldArea().x + x && static_cast<UINT64>(y)* tmxObj_.GetWorldArea().x + static_cast<UINT64>(x) < layer.second.size())
				{
					//int gid = tmxObj_.GetMapData(layer.first, x - tmxObj_.GetFirstgID(), y);
					int gid = layer.second[static_cast<UINT64>(y)* tmxObj_.GetWorldArea().x + static_cast<UINT64>(x)] - tmxObj_.GetFirstgID();
					if (gid >= 0)
					{
						DrawGraph(x * TileSize.x, y * TileSize.y + (Offset_* square_goresult_size), lpImageMng.GetID("tiles1.png")[gid], true);
					}
				}
			}

		}
	}
	int GoaloffsetG = 10;
	DrawGraph(static_cast<int>(GoalPos_.x), static_cast<int>(GoalPos_.y), lpImageMng.GetID("Re")[0], true);
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
		DrawExtendGraph(static_cast<int>(Playerpos_.x * static_cast<int>(square_goresult_size)- AdjustmentSize_),
			static_cast<int>(Playerpos_.y+ Offset_)* static_cast<int>(square_goresult_size)- (AdjustmentSize_*4)- UpMoveAnim_,
			static_cast<int>(Playerpos_.x )* static_cast<int>(square_goresult_size) + square_goresult_size - 1 + X_AdjustmentSize_ + AdjustmentSize_,
			static_cast<int>(Playerpos_.y+ Offset_) * static_cast<int>(square_goresult_size) + square_goresult_size - 1+(AdjustmentSize_*2)- UpMoveAnim_,
			lpImageMng.GetID("warp_640.png")[animCnt_ % animCntmax], true);
		//DrawGraph(0,0, lpImageMng.GetID("warp_6401.png")[0], true);
		if (animCnt_ % animCntmax < Spawn_moveMaxCnt_)
		{
			UpMoveAnim_ += 10;
			if (!CheckSoundMem(SE_))
			{

				PlaySoundMem(SE_, DX_PLAYTYPE_BACK, true);
			}
		}
	}
	else
	{
		DrawGraph(static_cast<int>(Playerpos_.x)* static_cast<int>(square_goresult_size),
			static_cast<int>(Playerpos_.y+ Offset_)* static_cast<int>(square_goresult_size)- Spawn_moveCnt_, lpImageMng.GetID("Player.png")[0], true);
		/*for (auto pos : Poslist_)
		{
			DrawGraph(static_cast<int>(pos.x)* static_cast<int>(square_goresult_size),
				static_cast<int>(pos.y+ Offset_)* static_cast<int>(square_goresult_size) - Spawn_moveCnt, lpImageMng.GetID("SP.png")[0], true);
		}*/
		if (Spawn_moveCnt_ < Spawn_moveMaxCnt_)
		{
			Spawn_moveCnt_++;
		}
		else
		{
			animflag_ = true;
		}
		
	}
	DrawExtendGraph(static_cast<int>(GoalEfPos_.x - GoaloffsetG), static_cast<int>(GoalEfPos_.y - ChipSize - GoaloffsetG), static_cast<int>(GoalEfPos_.x + ChipSize - 1 + GoaloffsetG), static_cast<int>(GoalEfPos_.y + ChipSize - 1 + GoaloffsetG), lpImageMng.GetID("Goal")[(GoalanimeCnt_ / 40) % 3 + 9], true);

	/*TRACE("%d\n", animCnt / 20 % animCntmax);*/
	//ownScene_->Draw();
	//afterScene_->Draw();
}

bool GoResultScene::Init(void)
{
	animCnt_ = 0;
	Spawn_moveCnt_ = 0;
	animflag_ = false;
	startflag_ = false;
	UpMoveAnim_ = 0;
	AdjustmentSize_ = 20;
	X_AdjustmentSize_ = 10;

	SE_ = LoadSoundMem("image/SE/warp.mp3");
	ChangeVolumeSoundMem(VolumeObjSE+50 , SE_);
	/*for (auto objList_)
	{

	}*/
	lpImageMng.GetID("image/Obj/Player.png", "Player.png", { 48,48 }, { 3,7 });
	lpImageMng.GetID("image/Obj/SP.png", "SP.png", { 48,48 }, { 3,5 });
	lpImageMng.GetID("image/start.png", "start.png", {120,240}, {9,1});
	lpImageMng.GetID("image/warp_640.png", "warp_640.png", { 640,480 }, { 2,13 });
	//lpImageMng.GetID("image/warp_640.png", "warp_6401.png");
	rapidxml::file<>objFileName = "tmx/objList1.tsx";
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
	}
	objctVec_ = objFileName.vecData();
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
			GoalPos_ = { objx* ChipSize ,(objy+1)* ChipSize };
			GoalEfPos_ = { objx * ChipSize ,(objy + 1) * ChipSize };
		}
	}
	return false;
}
