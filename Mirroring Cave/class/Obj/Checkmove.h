#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "Player.h"

#include "../../tmx/rapidxml.hpp"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/TmxObj.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
struct Checkdead
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		if (player->moveStop_checkdie_flag)
		{
			player->pos_.x += 24;
			return true;
		}
		return false;
	}
};
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

//位置補正方向
struct CorrectPosSx
{
	bool operator()(Vector2Dbl& pos_, Vector2Dbl& size_)
	{
		int posx = static_cast <int>(pos_.x);
		int sizex = static_cast <int>(size_.x);
		/*int posy = static_cast <int>(pos_.y);
		int sizey = static_cast <int>(size_.y);*/
		if ((posx % sizex) == 0 /*&& (posy % sizey) == 0*/)
		{

			return true;
		}
		/*pos_.x = ((posx + sizex / 2) / sizex) * sizex;
		return true;*/
		return false;
	}
};
struct CorrectPosSy
{
	bool operator()(Vector2Dbl& pos_, Vector2Dbl& size_)
	{
		/*int posx = static_cast <int>(pos_.x);
		int sizex = static_cast <int>(size_.x);*/
		int posy = static_cast <int>(pos_.y);
		int sizey = static_cast <int>(size_.y);
		if (/*(posx % sizex) == 0 &&*/ (posy % sizey) == 0)
		{

			return true;
		}
		/*pos_.x = ((posx + sizex / 2) / sizex) * sizex;
		return true;*/
		return false;
	}
};
struct TitleCheckObjR
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{

		auto player = dynamic_cast<Player*>(obj);

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Player)
				{
					continue;
				}
				//死んでるものをはじく 復活するものははじかない
				if (objlist->GetObjType() == objType::Torch)
				{
					if (objlist->moveStop_checkdie_flag == false)
					{
						continue;
					}
				}
				if (objlist->GetObjType() != objType::Torch)
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

				if (player->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					//当たった際の判定処理LRとUDがあるのでどこかで整理する
					if (objlist->GetObjType() == objType::Torch)
					{
						objlist->moveStop_checkdie_flag = false;
						int ecSE = LoadSoundMem("image/SE/explosion.mp3");
						ChangeVolumeSoundMem(VolumeObjSE, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
						player->CheckTitleHit_ = true;
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
struct CheckCollUnitLR
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{

		auto player = dynamic_cast<Player*>(obj);

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Player )
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Half)
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
				//死んでるものをはじく 復活するものははじかない
				
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

				if (player->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					//当たった際の判定処理LRとUDがあるのでどこかで整理する
					if (objlist->GetObjType() == objType::Goal)
					{
						objlist->moveStop_checkdie_flag = true;

					}
					if (objlist->GetObjType() == objType::OneWay)
					{
						if (player->dir_ == objlist->Moveabledir)
						{
							continue;
						}

					}
					/*if (objlist->GetObjType() == objType::Torch)
					{
						objlist->moveStop_checkdie_flag = false;
						int ecSE = LoadSoundMem("image/SE/explosion.mp3");
						ChangeVolumeSoundMem(100, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					}*/
					return false;
				}
				

			}
			return true;
		};		//moveVec　レイの元

		auto cntData = player->controller_->GetCntData();
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
struct CheckCollUnitUD
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		auto cntData = player->controller_->GetCntData();

		bool check_ignore_flag = false;

		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x, ray.p.y, ray.p.x + ray.vec.x, ray.p.y + ray.vec.y, 0xffffff);	//レイを飛ばす
			for (auto& objlist : objList_)
			{
				//ループ毎にフラグを初期化
				check_ignore_flag = false;
				//当たってはいけないものをはじく
				if (objlist->GetObjType() == objType::Player)
				{
					continue;
				}
				if (objlist->GetObjType() == objType::Half)
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
					check_ignore_flag = false;
					continue;
				}
					//_dbgDrawBox(objlist->pos_.x, objlist->pos_.y, objlist->pos_.x + objlist->size_.x, objlist->pos_.y + objlist->size_.y, 0xff0000, false);

				if (player->raycast_.CheckCollision(ray, { { objlist->pos_.x,objlist->pos_.y} , {objlist->size_.x,objlist->size_.y} }))
				{
					if (objlist->GetObjType() == objType::Goal)
					{
						objlist->moveStop_checkdie_flag = true;

					}
					if (objlist->GetObjType() == objType::OneWay)
					{
						if (player->dir_ == objlist->Moveabledir)
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
struct Move
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		for (auto atr = node->first_attribute();atr != nullptr;atr = atr->next_attribute())
		{
			
			std::string atrName = atr->name();
			/*if (player->animItrCnt_.state == "run")
			{
				CorrectPosy()(player->pos_, player->size_);
			}
			if(player->animItrCnt_.state == "Downrun" || player->animItrCnt_.state == "Uprun")
			{
				CorrectPosx()(player->pos_, player->size_);
			}*/
			/*else
			{
				CorrectPosy()(player->pos_, player->size_);
			}*/
			if (atrName == "x")
			{
				CorrectPosy()(player->pos_, player->size_);
				
				player->pos_.x += atof(atr->value());
				/*switch (player->dir_)
				{
				case MOVE_DIRECTION::LEFT:
					player->pos_.x += atof(atr->value());
					break;
				case MOVE_DIRECTION::RIGHT:
					player->pos_.x += atof(atr->value());
					break;
				default:
					break;
				}*/
			}
			if (atrName == "y")
			{
				CorrectPosx()(player->pos_, player->size_);
				player->pos_.y += atof(atr->value());
				/*switch (player->dir_)
				{
				case MOVE_DIRECTION::UP:
					player->pos_.y += atof(atr->value());
					break;
				case MOVE_DIRECTION::DOWN:
					player->pos_.y += atof(atr->value());
					break;
				default:
					break;
				}*/
			}
			//switch (player->dir_)
			//{
			//case MOVE_DIRECTION::LEFT:
			//	//CorrectPosy()(player->pos_, player->size_);
			//	if (CorrectPosSy()(player->pos_, player->size_))
			//	{
			//		player->pos_.x -= 4;
			//	}
			//	break;
			//case MOVE_DIRECTION::RIGHT:
			//	//CorrectPosy()(player->pos_, player->size_);
			//	if (CorrectPosSy()(player->pos_, player->size_))
			//	{
			//		player->pos_.x += 4;
			//	}
			//	break;
			//case MOVE_DIRECTION::UP:
			//	//CorrectPosx()(player->pos_, player->size_);
			//	if (CorrectPosSx()(player->pos_, player->size_))
			//	{
			//		player->pos_.y -= 4;
			//	}
			//	break;
			//case MOVE_DIRECTION::DOWN:
			//	//CorrectPosx()(player->pos_, player->size_);
			//	if (CorrectPosSx()(player->pos_, player->size_))
			//	{
			//		player->pos_.y += 4;
			//	}
			//	break;
			//default:
			//	break;
			//}
		}
		return true;
	}
};
//アニメーションのセット
struct SetAnime
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		std::string state =node->first_attribute("state")->value();
		player->animItrCnt_ =  lpAnimMng.SetAnimData(player->animItrCnt_.ObjID, state);//state
		return true;
	}
};
//ステータスのチェック
struct CheckState
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		auto Statenode  = node->first_attribute("state");
		/*std::string state = Statenode->value();*/
		std::string state = node->first_attribute("state")->value();
		if (player->animItrCnt_.state == state)
		{
			return true;
		}
		if (node->first_attribute("state")->next_attribute() == nullptr)
		{
			return false;
		}
		auto state2 = node->first_attribute("state2")->value();
		if (player->animItrCnt_.state == state2)
		{
			return true;
		}
		if (node->first_attribute("state2")->next_attribute() == nullptr)
		{
			return false;
		}
		/*while (Statenode)
		{
			if (player->animItrCnt_.state == Statenode->value())
			{
				return true;
			}

			Statenode = Statenode->next_attribute("state");
		}*/
		//state2,state3はIdleに戻す際に使う
		
		auto state3 = node->first_attribute("state3")->value();
		if (player->animItrCnt_.state == state3)
		{
			return true;
		}
		auto state4 = node->first_attribute("state4")->value();
		if (player->animItrCnt_.state == state4)
		{
			return true;
		}
	/*	auto state5 = node->first_attribute("state5")->value();
		if (player->animItrCnt_.state == state5)
		{
			return true;
		}*/
	
		//TRACE("ステータスチェック");
		return false;
	}

};
//マップとの当たり判定 左右
struct CheckCol
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		
		auto w = atof(node->first_attribute("w")->value());
		auto speedX = atof(node->first_attribute("speed")->value());
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(ray.p.x,ray.p.y,ray.p.x + ray.vec.x, ray.p.y + ray.vec.y,0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x+ coll.second.x, coll.first.y + coll.second.y,0xff0000,false);
				if (player->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元
		
		auto cntData = player->controller_->GetCntData();
		if (cntData[InputID::Left][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ -(speedX + w)	,	0 }))
			{
				
				player->dir_ = MOVE_DIRECTION::LEFT;
				
				return true;
			}
		}
		if (cntData[InputID::Right][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ speedX + w	,	0 }))
			{
				
				player->dir_ = MOVE_DIRECTION::RIGHT;
				
				return true;
			}
		}
		//CorrectPosy()(player->pos_, player->size_);
		
		return false;
	}
};
//マップとの当たり判定 上
struct CheckColUD
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto w = atof(node->first_attribute("w")->value());
		auto speedY = atof(node->first_attribute("speed")->value());
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x), static_cast<int>(ray.p.y), static_cast<int>(ray.p.x) + static_cast<int>(ray.vec.x), static_cast<int>(ray.p.y) + static_cast<int>(ray.vec.y), 0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x + coll.second.x, coll.first.y + coll.second.y, 0xff0000, false);
				if (player->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元

		auto cntData = player->controller_->GetCntData();
		
		if (cntData[InputID::Up][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, -(speedY + w) } /*halfsize_*/))
			{
				
				player->dir_ = MOVE_DIRECTION::UP;
				return true;
			}
		}
		/*if (cntData[InputID::Down][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, speedY + w }))
			{

				player->dir_ = MOVE_DIRECTION::DOWN;

				return  true;
			}
		}*/
		//CorrectPosx()(player->pos_, player->size_);
		return false;
	}
};
//マップとの当たり判定 下
struct CheckColD
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		auto ceneterX = atof(node->first_attribute("Checkcenterx")->value());
		auto ceneterY = atof(node->first_attribute("Checkcentery")->value());

		Vector2Dbl halfsize = Vector2Dbl{ ceneterX,ceneterY };
		auto w = atof(node->first_attribute("w")->value());
		auto speedY = atof(node->first_attribute("speed")->value());
		auto checkmove = [&](Vector2Dbl&& moveVec) {
			Raycast::Ray ray = { dynamic_cast<Player*>(obj)->pos_ + halfsize,moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x), static_cast<int>(ray.p.y), static_cast<int>(ray.p.x) + static_cast<int>(ray.vec.x), static_cast<int>(ray.p.y) + static_cast<int>(ray.vec.y), 0x00ff00);	//レイを飛ばす
			for (auto& coll : TmxObj.GetColList())
			{
				//_dbgDrawBox(coll.first.x, coll.first.y, coll.first.x + coll.second.x, coll.first.y + coll.second.y, 0xff0000, false);
				if (player->raycast_.CheckCollision(ray, coll))
				{
					return false;
				}
			}
			return true;
		};		//moveVec　レイの元

		auto cntData = player->controller_->GetCntData();
		
		/*if (dynamic_cast<Player*>(obj)->gravity_ < 0)
		{
			return true;
		}*/
		if (cntData[InputID::Down][static_cast<int>(Trg::Now)])
		{
			if (checkmove(Vector2Dbl{ 0	, speedY + w }))
			{
				
					player->dir_ = MOVE_DIRECTION::DOWN;
				
				return  true;
			}
		}
		//CorrectPosx()(player->pos_, player->size_);
		return false;
	}
};
// キーチェック　左右
struct CheckKeyLR
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "key")
			{

				std::string alr = atr->value();
				auto cntData = obj->controller_->GetCntData();
				if (cntData[InputID::Left][static_cast<int>(Trg::Now)] &&alr == "LEFT")
				{

					player->moveLR = DIR_LR::L;
					
					return true;

				}
				if (cntData[InputID::Right][static_cast<int>(Trg::Now)] && alr == "RIGHT")
				{

					player->moveLR = DIR_LR::R;
					return true;

				}
				else if (cntData[InputID::Left][static_cast<int>(Trg::Now)] == false &&
					cntData[InputID::Right][static_cast<int>(Trg::Now)] == false &&
					cntData[InputID::Down][static_cast<int>(Trg::Now)] == false &&
					cntData[InputID::Up][static_cast<int>(Trg::Now)] == false)
				{
					if (alr == "NON")
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};
// キーチェック　上下
struct CheckKeyUD
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			auto cntData = obj->controller_->GetCntData();
			if (atrName == "key")
			{
				std::string alr = atr->value();
				if (cntData[InputID::Up][static_cast<int>(Trg::Now)]  && alr == "Up")
				{
					return true;
				}
				if (cntData[InputID::Down][static_cast<int>(Trg::Now)]  && alr == "Down")
				{
					return true;
				}
			}
		}
		return false;
	}
};

struct Checkflag
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist& objList_)
	{
		auto player = dynamic_cast<Player*>(obj);
		//for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		//{
		//	std::string flagName = atr->name();
		//	bool flag = false;
		//	if (flagName == "true")
		//	{
		//		flag = true;
		//	}
		//	//フレンドしてない
		//	if (player->CheckHit)
		//	{
		//		return true;
		//	}
		//		
		//	
		//}
		return player->CheckTitleHit_;
	}
};
struct ModuleNode
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
	std::map <std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node, TmxObj& TmxObj, ObjUlist & objList_)>> modul_ = {
	  {"CheckKeyLR",CheckKeyLR()},
	{"CheckKeyUD",CheckKeyUD()} ,
	{"CheckCol",CheckCol()},
	{"CheckColUD",CheckColUD()} ,
	{"CheckColD",CheckColD()},
	{"Move",Move()},
	{"CheckState" ,CheckState()},
	{"SetAnime",SetAnime()},
	{"CheckCollUnitLR",CheckCollUnitLR()},
	{"CheckCollUnitUD",CheckCollUnitUD()},
	{"Checkflag",Checkflag()},
	{"TitleCheckObjR",TitleCheckObjR()},
	{"Checkdead",Checkdead()}
	};
};


