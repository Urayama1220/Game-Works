#include <DxLib.h>
#include "../common/imageMng.h"
#include "../Choice.h"

#include "SetupScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Transition/FadeinOut.h"
#include "Transition/CrossOver.h"
#include "GoResultScene.h"
#include "GameOverScene.h"

#include "../Obj/Player.h"
#include "../Obj/Supporter.h"
#include "../Obj/Hole.h"
#include "../Obj/Half.h"
#include "../Obj/Respawn.h"
#include "../Obj/Door.h"
#include "../Obj/DoorOpen.h"
#include "../Obj/Torch.h"
#include "../Obj/Goal.h"
#include "../Obj/Simultaneous.h"
#include "../Obj/Simultaneousdoor.h"
#include "../Obj/Pushbutton.h"
#include "../Obj/PushDoor.h"
#include "../Obj/ThornPath.h"
#include "../Obj/hint.h"
#include "../Obj/OneWay.h"


GameScene::GameScene()
{
	Init();
	DrawOwnScreen();
}
GameScene::GameScene(Stage Choice, Stagelist& Slist )
{
	ClearStagelist_ = std::move(Slist);
	Choice_ = Choice;
	RECnt_ = 0;
	Init();
}
GameScene::GameScene(Stage Choice, Stagelist& Slist, UniqueInput& imput)
{
	ClearStagelist_ = std::move(Slist);
	imput_ = std::move(imput);
	Choice_ = Choice;
	RECnt_ = 0;
	Init();
	
	DrawOwnScreen();
}
GameScene::GameScene(Stage Choice, Stagelist& Slist, int RECnt, UniqueInput& imput)
{
	ClearStagelist_ = std::move(Slist);
	imput_ = std::move(imput);
	Choice_ = Choice;
	RECnt_ = RECnt;
	Init();

	DrawOwnScreen();
}

GameScene::~GameScene()
{
}

uniqueScene GameScene::Update(uniqueScene ownScene)
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		//次のシーンに移行
		InitSoundMem();
		return std::make_unique<SetupScene>(Choice_, ClearStagelist_,ownScene, RECnt_);
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		//次のシーンに移行
		InitSoundMem();
		return std::make_unique<GoResultScene>(Choice_, ClearStagelist_, aftime, RECnt_, imput_, pos_);
	}
	/*for (const auto& hint : HintList_)
	{
		hint->Updata(tmxObj_, objList_);
	}*/
	for (const auto& obj : objList_)
	{
		obj->Updata(tmxObj_, objList_);
	}
	for (const auto& obj : objList_)
	{
		if (obj->GetObjType() == objType::Goal)
		{
			if (obj->moveStop_checkdie_flag == true)
			{
				InitSoundMem();
				
				return std::make_unique<GoResultScene>(Choice_, ClearStagelist_, aftime, RECnt_, imput_, pos_);
			}
		}
		if (obj->GetObjType() == objType::Player)
		{
			if (obj->GameOverMove_flag == true)
			{
				RECnt_++;
				InitSoundMem();
				return std::make_unique<CrossOver>(ownScene, std::make_unique<GameOverScene>(Choice_, ClearStagelist_, RECnt_, imput_, ownScene));
			}
		}
	}
	Timer();
	DrawOwnScreen();
	return ownScene;
}
void GameScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawExtendGraph(0, 0, static_cast<int>(screenSize_.x - 1), static_cast<int>(60), lpImageMng.GetID("background.png")[0], true);
	//DrawGraph(0, 0, lpImageMng.GetID("background.png")[0], true);
	//mapの描画
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
					int gid = layer.second[static_cast<UINT64>(y) * tmxObj_.GetWorldArea().x + static_cast<UINT64>(x) ] - tmxObj_.GetFirstgID();
					if (gid >= 0)
					{
						DrawGraph(x * TileSize.x, y * TileSize.y + (Offset_ * ChipSize), lpImageMng.GetID("tiles1.png")[gid], true);
					}
				}
			}

		}
	}
	/*TRACE("kore%d\n", Choice_);*/
	/*for (const auto& hint : HintList_)
	{
		hint->Draw();
	}*/
	for (const auto& obj : objList_)
	{
		if (obj->moveStop_checkdie_flag)
		{
			if (obj->GetObjType() != objType::Door)
			{
				if (obj->GetObjType() != objType::DoorOpen)
				{
					if (obj->GetObjType() != objType::PushDoor)
					{
						obj->Draw();
					}
				}
			}
			
		}
	}
	for (const auto& obj : objList_)
	{
		if (obj->moveStop_checkdie_flag)
		{
			if (obj->GetObjType() == objType::Door)
			{
				obj->Draw();
			}
			if (obj->GetObjType() == objType::DoorOpen)
			{
				obj->Draw();
			}
			if (obj->GetObjType() == objType::PushDoor)
			{
				obj->Draw();
			}

		}
	}
	for (const auto& obj : objList_)
	{
		if (!obj->moveStop_checkdie_flag)
		{
			obj->Draw();
		}
	}

	//マス目（消す予定）
	/*for (int x = 0; x < 39; x++)
	{
		for (int y = 0 ;y < 22; y++)
		{
			DrawLine(0 , y*48,1280,y*48,0xf0f0f0);
			DrawLine( x * 48,0, x * 48, 720 , 0xf0f0f0);
		}
	}*/
	//数値のけたを減らして代入
	/*DrawGraph(0, 0,, true);*/
	
	/*DrawGraph(0, 0, lpImageMng.GetID("thorn.png")[0], true);*/
	DrawTimer(aftime/1000.0f);
	DrawRestart();
	DrawGraph(11,8,lpImageMng.GetID("setting.png")[0],true);
	/*DrawFormatString(1000, 10, 0xffffff, "%d\n", RECnt_);
	DrawFormatString(900, 10, 0xffffff, "%d\n", aftime);*/
	/*DrawGraph(0, 0, lpImageMng.GetID("hole")[0], true);*/
}
bool GameScene::Init(void)
{
	//マップのロード
	LoadMap();
	//タイマーの初期値を入力
	StartTime = GetNowCount() - aftime;
	lpImageMng.GetID("image/Obj/thorn.png", "thorn.png");
	lpImageMng.GetID("image/number.png", "number.png", { 16,32 }, { 10,1 });
	lpImageMng.GetID("image/logo/game_reset.png", "game_reset.png");
	lpImageMng.GetID("image/logo/Time.png", "Time.png");
	lpImageMng.GetID("image/frameback.png", "frameback.png");
	lpImageMng.GetID("image/framebackTime.png", "framebackTime.png");
	lpImageMng.GetID("image/TimeNowCnt1.png", "TimeNowCnt.png");
	lpImageMng.GetID("image/ResetCntLogo.png", "ResetCntLogo.png");
	lpImageMng.GetID("image/setting.png", "setting.png");
	lpImageMng.GetID("image/colon.png", "colon.png");
	return true;
}

bool GameScene::Timer(void)
{
	//タイマー
	aftime = GetNowCount() - StartTime;
	if (aftime > 10000 && StartTime != 0)
	{
		/*TRACE("10秒経過\n");
		StartTime = GetNowCount();*/
		
		return true;
	}
	return false;
}

void GameScene::DrawTimer(float aftTime)
{
	int second = static_cast<int>(aftTime);
	int minute = second / 60;
	second %= 60;
	/*int hour = minute / 60;*/
	minute %= 60;
	
	std::string StringTime = std::to_string(minute);
	while (StringTime.length() != 2)
	{
		StringTime.insert(0, "0");
	}
	DrawGraph(740 - ChipSize, 18, lpImageMng.GetID("framebackTime.png")[0], true);
	DrawGraph(740- 36, 20, lpImageMng.GetID("TimeNowCnt.png")[0], true);
	//DrawGraph(740 - 48 * 2, 12, lpImageMng.GetID("Time.png")[0], true);
	DrawGraph(740 + 24 * 1.5, 26, lpImageMng.GetID("colon.png")[0], true);
	for (int i=0; i<2;i++)
	{
		int Num = atoi(StringTime.substr(i, 1).c_str());
		//DrawGraph(1000 + 48 * i, 120,,true);
		DrawGraph(740 + 20 * i, 22, lpImageMng.GetID("number.png")[Num], true);
		/*if (i < 2)
		{
			DrawGraph(740 + 20 * i, 22, lpImageMng.GetID("number.png")[Num], true);
		}
		else
		{
			DrawGraph(747 + 20 * i, 22, lpImageMng.GetID("number.png")[Num], true);
		}*/
		
	}
	std::string StringTimeS = std::to_string(second);
	while (StringTimeS.length() != 2)
	{
		StringTimeS.insert(0, "0");
	}
	for (int i = 0; i < 2; i++)
	{
		int Num = atoi(StringTimeS.substr(i, 1).c_str());
		DrawGraph(747 + 20 * (i+2), 22, lpImageMng.GetID("number.png")[Num], true);
	}
	//TRACE("second:%d minute:%d\n", second, minute);
}

void GameScene::DrawRestart(void)
{
	std::string StringTime = std::to_string(RECnt_);
	while (StringTime.length() != 2)
	{
		StringTime.insert(0, "0");
	}
	DrawGraph(1000 - 132, 18, lpImageMng.GetID("frameback.png")[0], true);
	DrawGraph(1000 - 122, 20, lpImageMng.GetID("ResetCntLogo.png")[0], true);
	//DrawGraph(840 , 12, lpImageMng.GetID("game_reset.png")[0], true);
	
	for (int i = 0; i < 2; i++)
	{
		int Num = atoi(StringTime.substr(i, 1).c_str());

		DrawGraph(1000 + 24 * i- ChipSize*1.5, 22, lpImageMng.GetID("number.png")[Num], true);
	}
	
}

bool GameScene::LoadMap(void)
{
	/*tmxObj_.LoadTMX("./tmx/map3.tmx");*/
	rapidxml::file<>objFileName = "tmx/objList1.tsx";
	//ステージセレクトの予定
	switch (Choice_)
	{
	case Stage::one:
		tmxObj_.LoadTMX("./tmx/map1.tmx");
		objFileName = "tmx/objList1.tsx";
		HintList_.emplace_back(std::make_unique<hint>(2, 2 + Offset_, false, "image/hintlogo/move.png", Vector2Dbl{2,1}));
		HintList_.emplace_back(std::make_unique<hint>(4, 7 + Offset_, false, "image/hintlogo/moveto.png"));
		HintList_.emplace_back(std::make_unique<hint>(11, 7 + Offset_, false, "image/hintlogo/Esc.png", Vector2Dbl{ 1.5,1 }));
		HintList_.emplace_back(std::make_unique<hint>(15, 11 + Offset_, false, "image/hintlogo/goal.png"));
		break;
	case Stage::two:
		tmxObj_.LoadTMX("./tmx/map2.tmx");
		objFileName = "tmx/objList2.tsx";
		HintList_.emplace_back(std::make_unique<hint>(5, 4 + Offset_, false, "image/hintlogo/road.png", Vector2Dbl{ -2,0 }));
		HintList_.emplace_back(std::make_unique<hint>(13, 10 + Offset_, false, "image/hintlogo/oneway.png", Vector2Dbl{ 1,0 }));

		break;
	case Stage::three:
		tmxObj_.LoadTMX("./tmx/map3.tmx");
		objFileName = "tmx/objList3.tsx";
		//HintList_.emplace_back(std::make_unique<hint>(17, 9 + Offset_, false, "image/hintlogo/robogoal.png"));
		break;
	case Stage::four:
		tmxObj_.LoadTMX("./tmx/map4.tmx");
		objFileName = "tmx/objList4.tsx";
		HintList_.emplace_back(std::make_unique<hint>(12, 2 + Offset_, false, "image/hintlogo/kitorch.png", Vector2Dbl{ 1,0 }));
		HintList_.emplace_back(std::make_unique<hint>(4,8 + Offset_, false, "image/hintlogo/ntorch.png", Vector2Dbl{ 2,0 }));
		HintList_.emplace_back(std::make_unique<hint>(2, 2 + Offset_, false, "image/hintlogo/torch.png"));
		HintList_.emplace_back(std::make_unique<hint>(10, 2 + Offset_, false, "image/hintlogo/torch2.png", Vector2Dbl{ 1,0 }));
		break;
	case Stage::five:
		tmxObj_.LoadTMX("./tmx/map5.tmx");
		objFileName = "tmx/objList5.tsx";
		HintList_.emplace_back(std::make_unique<hint>(9, 5 + Offset_, false, "image/hintlogo/mizu.png", Vector2Dbl{ 2,0 }));
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
		HintList_.emplace_back(std::make_unique<hint>(9, 5 + Offset_, false, "image/hintlogo/push.png", Vector2Dbl{ -1,0 }));
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
		HintList_.emplace_back(std::make_unique<hint>(8, 7 + Offset_, false, "image/hintlogo/toge.png", Vector2Dbl{ 2.5,0 }));
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
	case Stage::sixteen:
		tmxObj_.LoadTMX("./tmx/map16.tmx");
		objFileName = "tmx/objList16.tsx";
		break;
	default:
		
	
		HintList_.emplace_back(std::make_unique<hint>(11, 2 + Offset_, false, "image/hintlogo/reba.png"));
	
		break;
	}
	//else //Choice::zeroの場合
	//{
	//	tmxObj_.LoadTMX("./tmx/map3.tmx");
	//	objFileName = "tmx/objList.tsx";
	//}
	objctVec_ = objFileName.vecData();
	objctDoc.parse<0>(objctVec_.data());
	objctNode_ = objctDoc.first_node("objctList");

	/*auto width = objctNode_->first_attribute("tilewidth")->value();
	auto height = objctNode_->first_attribute("tileheight")->value();*/

	std::string TipsValue = objctNode_->first_attribute("TipsValue")->value();

	auto node = objctNode_->first_node("objList");
	/*Tips_ = TipsValue;*/
	for (auto ListNode = node->first_node("List"); ListNode != nullptr; ListNode = ListNode->next_sibling())
	{
		std::string listname = ListNode->first_attribute("name")->value();
		auto objx = atof(ListNode->first_attribute("x")->value());
		auto objy = atof(ListNode->first_attribute("y")->value());
		std::string dieValue = ListNode->first_attribute("die")->value();
		
		bool die;

		objy += Offset_;
		if (dieValue == "true")
		{
			die = true;
		}
		else
		{
			die = false;
		}
		if (listname == "Player")
		{
			
			objList_.emplace_back(std::make_unique<Player>(objx, objy, die, HintList_));
		}
		if (listname == "Supporter")
		{
			objList_.emplace_back(std::make_unique<Supporter>(objx, objy, die));
		}
		if (listname == "Hole")
		{
			objList_.emplace_back(std::make_unique<Hole>(objx, objy, die));
		}
		if (listname == "Half")
		{
			objList_.emplace_back(std::make_unique<Half>(objx, objy, die));
		}
		if (listname == "Respawn")
		{
			objList_.emplace_back(std::make_unique<Respawn>(objx, objy, die));
		}
		if (listname == "Door")
		{
			objList_.emplace_back(std::make_unique<Door>(objx, objy, die));
		}
		if (listname == "Torch")
		{
			objList_.emplace_back(std::make_unique<Torch>(objx, objy, die));
		}
		if (listname == "Goal")
		{
			pos_ = { objx ,objy-1 };
			objList_.emplace_back(std::make_unique<Goal>(objx, objy, die));
		}
		if (listname == "DoorOpen")
		{
			objList_.emplace_back(std::make_unique<DoorOpen>(objx, objy, die));
		}
		if (listname == "Simultaneous")
		{
			objList_.emplace_back(std::make_unique<Simultaneous>(objx, objy, die));
		}
		if (listname == "Simultaneousdoor")
		{
			objList_.emplace_back(std::make_unique<Simultaneousdoor>(objx, objy, die));
		}
		if (listname == "Pushbutton")
		{
			objList_.emplace_back(std::make_unique<Pushbutton>(objx, objy, die));
		}
		if (listname == "PushDoor")
		{
			objList_.emplace_back(std::make_unique<PushDoor>(objx, objy, die));
		}
		if (listname == "ThornPath")
		{
			objList_.emplace_back(std::make_unique<ThornPath>(objx, objy, die));
		}
		if (listname == "OneWay")
		{
			auto dirValue = atof(ListNode->first_attribute("dir")->value());
			MOVE_DIRECTION Dir = static_cast<MOVE_DIRECTION>(dirValue);
			objList_.emplace_back(std::make_unique<OneWay>(objx, objy, die, Dir));
		}
		/*createclass(listname,objx,objy);*/
		
		/*objList_.emplace_back(std::make_unique<Supporter>());
		objList_.emplace_back(std::make_unique<Hole>());
		objList_.emplace_back(std::make_unique<Half>());
		objList_.emplace_back(std::make_unique<Respawn>());*/
		
	}
	
	return true;
}
