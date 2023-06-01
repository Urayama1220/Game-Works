#include <DxLib.h>
#include "HalfwayScene.h"
#include "GameScene.h"
#include "../common/imageMng.h"
HalfwayScene::HalfwayScene()
{
	Choice_ = Stage::zero;
	Init();
	DrawOwnScreen();
}
HalfwayScene::HalfwayScene(Stage Choice, Stagelist& Slist,UniqueInput& imput)
{
	ClearStagelist_ = std::move(Slist);
	imput_ = imput;
	Choice_ = Choice;
	Init();
	DrawOwnScreen();
}
HalfwayScene::HalfwayScene(Stage Choice, Stagelist& Slist, int RECnt, UniqueInput& imput)
{
	RECnt_ = RECnt;
	ClearStagelist_ = std::move(Slist);
	imput_ = imput;
	Choice_ = Choice;
	Init();
	DrawOwnScreen();
}

HalfwayScene::~HalfwayScene()
{
}

uniqueScene HalfwayScene::Update(uniqueScene ownScene)
{
	if (startflag_)
	{
		return std::make_unique<GameScene>(Choice_, ClearStagelist_,RECnt_, imput_);
	}
	if (animCnt_ / animSize % animCntmax <= 4)
	{
		animCnt_++;
	}
	else
	{
		animflag_ = true;
	}
	DrawOwnScreen();
	return ownScene;
}

void HalfwayScene::DrawOwnScreen()
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
						DrawGraph(x * TileSize.x, y * TileSize.y + (Offset_* square_size), lpImageMng.GetID("tiles1.png")[gid], true);
					}
				}
			}

		}
	}
	if (!animflag_)
	{
		//光の柱
		DrawGraph(static_cast<int>(Playerpos_.x)* static_cast<int>(square_size) - StartAnimOffset_X_,
			static_cast<int>(Playerpos_.y+ Offset_)* static_cast<int>(square_size) - StartSize_ + StartAnimOffset_Y_,lpImageMng.GetID("start.png")[animCnt_ / animSize % 5], true);
		for (auto pos : Poslist_)
		{
			DrawGraph(static_cast<int>(pos.x)* static_cast<int>(square_size) - StartAnimOffset_X_,
				static_cast<int>(pos.y+ Offset_)* static_cast<int>(square_size) - StartSize_ + StartAnimOffset_Y_,lpImageMng.GetID("start.png")[animCnt_ / animSize % 5], true);
		}
	}
	else
	{
		//プレイヤーの表示
		DrawGraph(static_cast<int>(Playerpos_.x)* static_cast<int>(square_size),
			static_cast<int>(Playerpos_.y+ Offset_)* static_cast<int>(square_size)-(Objoffset_*2)+ Spawn_moveCnt, lpImageMng.GetID("Player.png")[0], true);
		for (auto pos : Poslist_)
		{
			DrawGraph(static_cast<int>(pos.x)* static_cast<int>(square_size),
				static_cast<int>(pos.y+ Offset_)* static_cast<int>(square_size)- (Objoffset_*2) + Spawn_moveCnt, lpImageMng.GetID("SP.png")[0], true);
		}
		if (Spawn_moveCnt< Spawn_moveMaxCnt_)
		{
			Spawn_moveCnt++;
		}
		else 
		{
			startflag_ = true;
		}
		
	}
	/*TRACE("%d\n", animCnt / 20 % animCntmax);*/
	//ownScene_->Draw();
	//afterScene_->Draw();
}

bool HalfwayScene::Init(void)
{
	animCnt_ = 0;
	Spawn_moveCnt = 0;
	animflag_ = false;
	startflag_ = false;
	Spawn_moveMaxCnt_ = 20; 
	StartSize_ = 248;
	StartAnimOffset_X_ = 38;
	StartAnimOffset_Y_ = 58;
	Objoffset_ = 20;
	lpImageMng.GetID("image/Obj/Player.png", "Player.png", { 48,48 }, { 3,7 });
	lpImageMng.GetID("image/Obj/SP.png", "SP.png", { 48,48 }, { 3,5 });
	lpImageMng.GetID("image/start.png", "start.png", {120,240}, {9,1});

	/*lpImageMng.GetID("image/Arrow.png", "Arrow.png");
	lpImageMng.GetID("image/logo/gamereturn.png", "gamereturn.png");
	lpImageMng.GetID("image/logo/restart.png", "restart.png");
	lpImageMng.GetID("image/logo/select.png", "select.png");
	lpImageMng.GetID("image/logo/title.png", "title.png");
	lpImageMng.GetID("image/logo/tips.png", "tips.png");
	lpImageMng.GetID("image/tegami1.png", "tegami1.png");
	lpImageMng.GetID("image/ant1.png", "syber1mini.png");*/
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
	case Stage::sixteen:
		tmxObj_.LoadTMX("./tmx/map16.tmx");
		objFileName = "tmx/objList16.tsx";
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
		if (listname == "Player")
		{
			Playerpos_ = { objx, objy };
		}
		if (listname == "Supporter")
		{
			Poslist_.emplace_back(Vector2Dbl{ objx, objy });
		}
	}
	return false;
}
