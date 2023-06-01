#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "Supporter.h"

#include "../../tmx/rapidxml.hpp"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/TmxObj.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

//位置補正x方向
struct CorrectPosx
{
	bool operator()(Vector2Dbl& pos_, Vector2Dbl& size_)
	{
		int posx = static_cast <int>(pos_.x);
		int sizex = static_cast <int>(size_.x);
		if ((posx % sizex) == 0)
		{

			return false;
		}
		int posy = static_cast <int>(pos_.y);
		int sizey = static_cast <int>(size_.y);
		if ((posy % sizey) == 0)
		{

			return false;
		}
		pos_.x = ((posx + sizex / 2) / sizex) * sizex;
		return true;
	}
};
//位置補正y方向
struct CorrectPosy
{
	bool operator()(Vector2Dbl& pos_, Vector2Dbl& size_)
	{
		int posx = static_cast <int>(pos_.x);
		int sizex = static_cast <int>(size_.x);
		if ((posx % sizex) == 0)
		{

			return false;
		}
		int posy = static_cast <int>(pos_.y);
		int sizey = static_cast <int>(size_.y);
		if ((posy % sizey) == 0)
		{

			return false;
		}
		pos_.y = ((posy + sizey / 2) / sizey) * sizey;
		return true;
	}
};
//ロボットが穴に落ちているか確認
struct Checkdie
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		for (auto& objlist : objList_)
		{
			if (objlist->GetObjType() == objType::Supporter)
			{
				if (objlist->moveStop_checkdie_flag)
				{
					return true;
				}
			}
		}
		return false;
	}
};

struct TitleCheckObjRSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{

		auto SP = dynamic_cast<Supporter*>(obj);

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Supporter)
				{
					continue;
				}
				//死んでるものをはじく 復活するものははじかない

				/*if (objlist->GetObjType() != objType::Torch)*/
				{
					if (objlist->GetObjType() != objType::PushDoor)
					{

						check_ignore_flag = true;

					}
				}
				//死んでるものをはじく
				if (objlist->moveStop_checkdie_flag && check_ignore_flag)
				{
					continue;
				}

				//_dbgDrawBox(objlist->pos_.x, objlist->pos_.y, objlist->pos_.x + objlist->size_.x, objlist->pos_.y + objlist->size_.y, 0xff0000, false);

				if (SP->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					//当たった際の判定処理LRとUDがあるのでどこかで整理する
					if (objlist->GetObjType() == objType::Torch)
					{
						objlist->moveStop_checkdie_flag = true;
						SP->CheckTitleHitSP_ = true;
						/*int ecSE = LoadSoundMem("image/SE/explosion.mp3");
						ChangeVolumeSoundMem(100, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);*/
					}
					return false;
				}


			}
			return true;
		};		//moveVec　レイの元


		if (checkmove(Vector2Dbl{ speedX + w	,	0 }))
		{
			return true;
		}

		return false;
	}
};
//オブジェクトとの当たり判定 左右
struct CheckCollUnitLRSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());



		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Supporter)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Torch)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Respawn)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Pushbutton)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::ThornPath)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Simultaneous)
				{
					continue;
				}
				
				if (objlist->GetObjType() != objType::Torch)
				{
					if (objlist->GetObjType() != objType::PushDoor)
					{
						if (objlist->GetObjType() != objType::Simultaneousdoor)
						{
							if (objlist->GetObjType() != objType::Door)
							{
								if (objlist->GetObjType() != objType::DoorOpen)
								{
									check_ignore_flag = true;
								}
							}
						}
					}
				}
				//死んでるものをはじく
				if (objlist->moveStop_checkdie_flag && check_ignore_flag)
				{
					continue;
				}
				//_dbgDrawBox(objlist->pos_.x, objlist->pos_.y, objlist->pos_.x + objlist->size_.x, objlist->pos_.y + objlist->size_.y, 0xff0000, false);

				if (SP->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					//当たった際の判定処理LRとUDがあるのでどこかで整理する
					if (objlist->GetObjType() == objType::Hole)
					{
						objlist->moveStop_checkdie_flag = true;
						SP->moveStop_checkdie_flag = true;
						SP->pos_ = objlist->pos_;
					}
					if (objlist->GetObjType() == objType::OneWay)
					{
						if (SP->dir_ == objlist->Moveabledir)
						{
							continue;
						}

					}
					return false;
				}


			}
			return true;
		};		//moveVec　レイの元

		auto cntData = SP->controller_->GetCntData();
		if (cntData[InputID::Left][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ -(speedX + w)	,	0 }))
			{
				return true;
			}
		}
		if (cntData[InputID::Right][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ speedX + w	,	0 }))
			{
				return true;
			}
		}
		return false;
	}
};
//オブジェクトとの当たり判定 上下
struct CheckCollUnitUDSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		auto cntData = SP->controller_->GetCntData();

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Supporter)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Respawn)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Torch)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Pushbutton)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::ThornPath)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Simultaneous)
				{
					continue;
				}
				//死んでるものをはじく
				
				if (objlist->GetObjType() != objType::Torch)
				{
					if (objlist->GetObjType() != objType::PushDoor)
					{
						if (objlist->GetObjType() != objType::Simultaneousdoor)
						{
							if (objlist->GetObjType() != objType::Door)
							{
								if (objlist->GetObjType() != objType::DoorOpen)
								{
									check_ignore_flag = true;
								}
							}
						}
					}
				}
				//死んでるものをはじく
				if (objlist->moveStop_checkdie_flag && check_ignore_flag)
				{
					continue;
				}
				//_dbgDrawBox(objlist->pos_.x, objlist->pos_.y, objlist->pos_.x + objlist->size_.x, objlist->pos_.y + objlist->size_.y, 0xff0000, false);

				if (SP->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					//当たった際の判定処理LRとUDがあるのでどこかで整理する
					if (objlist->GetObjType() == objType::Hole)
					{
						objlist->moveStop_checkdie_flag = true;
						SP->moveStop_checkdie_flag = true;
						SP->pos_ = objlist->pos_;
						
					}
					if (objlist->GetObjType() == objType::OneWay)
					{
						if (SP->dir_ == objlist->Moveabledir)
						{
							continue;
						}

					}
					return false;
				}


			}
			return true;
		};		//moveVec　レイの元

		
		if (cntData[InputID::Up][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, -(speedX + w) } /*halfsize_*/))
			{
				return true;
			}
		}
		if (cntData[InputID::Down][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, speedX + w }))
			{

				return  true;
			}
		}
		return false;
	}
};
//移動
struct MoveSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		for (auto atr = node->first_attribute();atr != nullptr;atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "x")
			{
				CorrectPosy()(SP->pos_, SP->size_);
				SP->pos_.x += atof(atr->value());
			}
			if (atrName == "y")
			{
				CorrectPosx()(SP->pos_, SP->size_);
				SP->pos_.y += atof(atr->value());
			}

		}
		return true;
	}
};
//アニメーションのセット
struct SetAnimeSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		std::string state =node->first_attribute("state")->value();
		SP->animItrCnt_ =  lpAnimMng.SetAnimData(SP->animItrCnt_.ObjID, state);//state
		//TRACE("ステータス変更");
		return true;
	}
};
//ステータスのチェック
struct CheckStateSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		std::string state = node->first_attribute("state")->value();
		if (SP->animItrCnt_.state == state)
		{
			return true;
		}
		if (node->first_attribute("state")->next_attribute() == nullptr)
		{
			return false;
		}
		auto state2 = node->first_attribute("state2")->value();
		if (SP->animItrCnt_.state == state2)
		{
			return true;
		}
		if (node->first_attribute("state2")->next_attribute() == nullptr)
		{
			return false;
		}
		auto state3 = node->first_attribute("state3")->value();
		if (SP->animItrCnt_.state == state3)
		{
			return true;
		}
		//TRACE("ステータスチェック");
		return false;
	}

};
//マップとの当たり判定 左右
struct CheckColSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());
		//_dbgDrawLine(SP->pos_.x + ceneterX, SP->pos_.y, SP->pos_.x + ceneterX, SP->pos_.y + ceneterY, 0x00ff00);	//レイを飛ばす
		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x), static_cast<int>(ray.p.y), static_cast<int>(ray.p.x) + static_cast<int>(ray.vec.x), static_cast<int>(ray.p.y) + static_cast<int>(ray.vec.y), 0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x+ coll.second.x, coll.first.y + coll.second.y,0xff0000,false);
				if (SP->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元
		
		auto cntData = SP->controller_->GetCntData();

		

		if (cntData[InputID::Left][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ -(speedX + w)	,	0 }))
			{
				SP->dir_ = MOVE_DIRECTION::LEFT;
				return true;
			}
		}
		if (cntData[InputID::Right][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ speedX + w	,	0 }))
			{
				SP->dir_ = MOVE_DIRECTION::RIGHT;
				return true;
			}
		}
		
		
		return false;
	}
};
//マップとの当たり判定 上
struct CheckColUSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto w = atof(node->first_attribute("w")->value());
		auto speedY = atof(node->first_attribute("speed")->value());
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x), static_cast<int>(ray.p.y), static_cast<int>(ray.p.x) + static_cast<int>(ray.vec.x), static_cast<int>(ray.p.y) + static_cast<int>(ray.vec.y), 0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x + coll.second.x, coll.first.y + coll.second.y, 0xff0000, false);
				if (SP->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元
		auto cntData = SP->controller_->GetCntData();
		
		if (cntData[InputID::Up][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, -(speedY + w) } /*halfsize_*/))
			{
				SP->dir_ = MOVE_DIRECTION::UP;
				return true;
			}
		}
		
		return false;
	}
};
//マップとの当たり判定 下
struct CheckColDSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());
		

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto w = atof(node->first_attribute("w")->value());
		auto speedY = atof(node->first_attribute("speed")->value());
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Supporter*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x), static_cast<int>(ray.p.y), static_cast<int>(ray.p.x) + static_cast<int>(ray.vec.x), static_cast<int>(ray.p.y) + static_cast<int>(ray.vec.y), 0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x + coll.second.x, coll.first.y + coll.second.y, 0xff0000, false);
				if (SP->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元

		auto cntData = SP->controller_->GetCntData();
		
		if (cntData[InputID::Down][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, speedY + w }))
			{
				SP->dir_ = MOVE_DIRECTION::DOWN;
				return  true;
			}
		}
		return false;
	}
};
// キーチェック　左右
struct CheckKeyLRSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "key")
			{
				
				std::string alr = atr->value();
				auto cntData = obj->controller_->GetCntData();
				if (cntData[InputID::Left][static_cast<int>(Trg::Now)] && alr == "LEFT")
				{
					SP->moveLR = DIR_LR::L;
					return true;
					
				}
				if (cntData[InputID::Right][static_cast<int>(Trg::Now)]&& alr == "RIGHT")
				{
					SP->moveLR = DIR_LR::R;
					return true;
					
				}
				/*else if (cntData[InputID::Left][static_cast<int>(Trg::Now)]  == false &&
					cntData[InputID::Right][static_cast<int>(Trg::Now)] ==false &&
					cntData[InputID::Down][static_cast<int>(Trg::Now)] == false&&
					cntData[InputID::Up][static_cast<int>(Trg::Now)] == false)
				{
					if (alr == "NON")
					{
						return true;
					}
				}*/
			}
		}
		return false;
	}
};
// キーチェック　上下
struct CheckKeyUDSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			
			std::string atrName = atr->name();
			if (atrName == "key")
			{
				std::string alr = atr->value();
				if ( alr == "Up")
				{
						return true;
				}
				if (alr == "Down")
				{
					return true;
				}
			}
		}
		return false;
	}
};

struct CheckflagSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto SP = dynamic_cast<Supporter*>(obj);
		
		//for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		//{
		//	std::string flagName = atr->name();
		//	bool flag = false;
		//	if (flagName == "true")
		//	{
		//		flag = true;
		//	}
		//	//フレンドしてない
		//	for (auto& obj : objList_)
		//	{
		//		if (obj->GetObjType() == objType::Torch)
		//		{
		//			if (obj->moveStop_checkdie_flag == flag)
		//			{

		//				return true;
		//			}
		//		}
		//	}


		//}
		return SP->CheckTitleHitSP_;
	}
};
struct ModuleNodeSP
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		for (auto Modulenode = node->first_node(); Modulenode != nullptr; Modulenode = Modulenode->next_sibling())
		{
			std::string Modulename = Modulenode->first_attribute("name")->value();
			if (modul_.count(Modulename))
			{
				//TRACE("%s", Modulename.c_str());
				if (!modul_[Modulename](obj, Modulenode, TmxObj, objList_))
				{
					//TRACE("->false\n");
					continue;
				}
				//TRACE("->true\n");
				if (!(*this)(obj, Modulenode, TmxObj, objList_))//!再起呼び出し
				{
					return false;
				}
					
			}
		}
		return true;
	};
	std::map <std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)>> modul_ = {
	{"CheckKeyLRSP",CheckKeyLRSP()},
	{"CheckKeyUDSP",CheckKeyUDSP()} ,
	{"CheckColSP",CheckColSP()},
	{"CheckColUSP",CheckColUSP()} ,
	{"CheckColDSP",CheckColDSP()},
	{"MoveSP",MoveSP()},
	{"CheckStateSP" ,CheckStateSP()},
	{"SetAnimeSP",SetAnimeSP()},
	{"CheckCollUnitLRSP",CheckCollUnitLRSP()},
	{"CheckCollUnitUDSP",CheckCollUnitUDSP()},
	{"Checkdie",Checkdie()},
	{"CheckflagSP",CheckflagSP()},
	{"TitleCheckObjRSP",TitleCheckObjRSP()}
	};
};


