#pragma once
#include "../../tmx/TmxObj.h"
#include "../common/Raycast.h"
#include "AnimMng.h"
#include "Obj.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
//struct Default_Pushback
//{
//	bool operator()(Vector2Dbl& pos_, Vector2Dbl& size_, Vector2Dbl& spos_, Vector2Dbl& ssize_)
//	{
//		//当たった際の反発処理（動くものと動かない物の時のみ使用）
//		double half = 2.0;
//		Vector2Dbl sps = pos_ + (size_ / half);
//		Vector2Dbl exSize = size_ / half;
//
//		Vector2Dbl Spos = spos_ + (ssize_ / half);
//		Vector2Dbl SxSize = ssize_ / half;
//		Vector2Dbl Sspos = Spos - sps;
//
//		auto diffx = SxSize.x + exSize.x - abs(Spos.x - sps.x);
//		auto diffy = SxSize.y + exSize.y - abs(Spos.y - sps.y);
//		auto Signx = Spos.x - sps.x;
//		auto Signy = Spos.y - sps.y;
//		Signx /= abs(Signx);
//		Signy /= abs(Signy);
//		if (diffx < diffy)
//		{
//			/*diffx *= 0.5;*/
//			pos_.x -= Signx * diffx;
//			return true;
//		}
//		else
//		{
//			/*diffy *= 0.5;*/
//			pos_.y -= Signy * diffy;
//			return true;
//		}
//		return false;
//	}
//};



struct isHit
{
	bool operator()(Vector2Dbl& Sspos_, Vector2Dbl& size_, Vector2Dbl& ssize_)
	{
		//四角同士の当たり判定
		if (abs(Sspos_.x) < abs(size_.x + ssize_.x) &&
			abs(Sspos_.y) < abs(size_.y + ssize_.y))
		{
			return true;
		}
		return false;
	}
};
struct PlayerhintHit
{
	void operator()(Vector2Dbl& pos_, Vector2Dbl& size_, ObjUlist& hintList_)
	{
		double half = 2.0;
		//自分の真ん中を取ってる
		Vector2Dbl spos = pos_ + (size_ / half);
		Vector2Dbl sSize = size_ / half;
		for (auto& obj : hintList_)
		{
			Vector2Dbl epos = obj->pos_ + (obj->size_ / half);
			Vector2Dbl eSize = obj->size_ / half;
			Vector2Dbl Sspos = epos - spos;
			Vector2Dbl halfsize = lpAnimMng.divsize / static_cast<double>(2);
			if (isHit()(Sspos, sSize, eSize))
			{
				obj->moveStop_checkdie_flag = true;
			}
			else
			{
				obj->moveStop_checkdie_flag = false;
			}
		}
	}
};
struct Collide
{
	//プレイヤーのギミックへの当たり判定
	uniCon operator()(Vector2Dbl& pos_, Vector2Dbl& size_, ObjUlist& objList_ ,uniCon controller_, bool& moveStop_checkdie_flag)
	{
		double half = 2.0;
		//自分の真ん中を取ってる
		Vector2Dbl spos = pos_ + (size_ / half);
		Vector2Dbl sSize = size_ / half;
		//_dbgDrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xff0000, false);

		bool flag = false;
		for (auto& obj : objList_)
		{
			//動けず死んでるオブジェクトは飛ばす
			/*if (obj->GetObjType() != objType::Torch)*/
			/*{
				if (obj->moveStop_checkdie_flag && obj->GetObjType() != objType::Torch)
				{
					continue;
				}
			}*/
			
			if (obj->GetObjType() != objType::Torch)
			{
				if (obj->GetObjType() != objType::Pushbutton)
				{
					if (obj->GetObjType() != objType::Door)
					{
						if (obj->GetObjType() != objType::DoorOpen)
						{
							if (obj->moveStop_checkdie_flag)
							{
								continue;
							}
						}
					}
				}
			}
			if (obj->GetObjType() == objType::Torch)
			{
				if (!obj->moveStop_checkdie_flag)
				{
					continue;
				}
			}
			auto cntData = controller_->GetCntData();
			//相手の真ん中を取ってる
			Vector2Dbl epos = obj->pos_ + (obj->size_ / half);
			Vector2Dbl eSize = obj->size_ / half;
			Vector2Dbl Sspos = epos - spos;

			Vector2Dbl halfsize = lpAnimMng.divsize / static_cast<double>(2);


			if (obj->GetObjType() == objType::Torch)
			{
				//_dbgDrawBox(obj->pos_.x, obj->pos_.y, obj->pos_.x + obj->size_.x, obj->pos_.y + obj->size_.y, 0xff0000, false);
				if (isHit()(Sspos, sSize, eSize))
				{
					//if (cntData[InputID::Btn1][static_cast<int>(Trg::Now)])
					{
						obj->moveStop_checkdie_flag = false;
						int ecSE = LoadSoundMem("image/SE/explosion.mp3");
						ChangeVolumeSoundMem(VolumeObjSE, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					}
					continue;
				}
			}
			if (obj->GetObjType() == objType::Simultaneous)
			{
				if (isHit()(Sspos, sSize, eSize))
				{
					//if (cntData[InputID::Btn1][static_cast<int>(Trg::Now)])
					{
						obj->moveStop_checkdie_flag = true;
					}
					continue;
				}
			}
			Vector2Dbl pos1 = obj->pos_ + Vector2Dbl{ 20, 40 };
			Vector2Dbl epos1 = pos1 + ((obj->size_ - Vector2Dbl{40, 50}) / half);
			Vector2Dbl eSize1 = (obj->size_ - Vector2Dbl{ 40, 50 }) / half;
			Vector2Dbl Sspos1 = epos1 - spos;
			
			if (obj->GetObjType() == objType::Door)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					moveStop_checkdie_flag = true;
				}
			}
			if (obj->GetObjType() == objType::DoorOpen)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					moveStop_checkdie_flag = true;
				}
			}
			////何かわからんけど、うまくいった
			/*if (obj->GetObjType() == objType::Pushbutton)
			{
				obj->moveStop_checkdie_flag = false;
				if (isHit()(Sspos, sSize, eSize))
				{
					obj->moveStop_checkdie_flag = true;
					flag = true;
					continue;
				}

			}*/
			if (obj->GetObjType() == objType::PushDoor)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					moveStop_checkdie_flag = true;
				}
				/*if (flag)
				{
					obj->moveStop_checkdie_flag = true;
					continue;
				}
				else
				{
					obj->moveStop_checkdie_flag = false;
					continue;
				}*/
			}

		}
		
			
		
		return controller_;
	}
};
struct CollideS
{
	//緑ブロックのギミックへの当たり判定
	uniCon operator()(Vector2Dbl& pos_, Vector2Dbl& size_, ObjUlist& objList_, uniCon controller_, bool& moveStop_checkdie_flag)
	{
		
		double half = 2.0;
		//自分の真ん中を取ってる
		Vector2Dbl spos = pos_ + (size_ / half);
		Vector2Dbl sSize = size_ / half;
		bool cflag = false;
		for (auto& obj : objList_)
		{
			//動けず死んでるオブジェクトは飛ばす
			//動けず死んでるオブジェクトは飛ばす
			if (obj->GetObjType() != objType::Torch)
			{
				if (obj->GetObjType() != objType::Door)
				{
					if (obj->GetObjType() != objType::DoorOpen)
					{
						if (obj->GetObjType() != objType::Pushbutton)
						{
							if (obj->GetObjType() != objType::PushDoor)
							{
								if (obj->moveStop_checkdie_flag)
								{
									continue;
								}
							}
						}
					}
				}
			}
			auto cntData = controller_->GetCntData();
			//相手の真ん中を取ってる
			Vector2Dbl epos = obj->pos_ + (obj->size_ / half);
			Vector2Dbl eSize = obj->size_ / half;
			Vector2Dbl Sspos = epos - spos;

			Vector2Dbl halfsize = lpAnimMng.divsize / static_cast<double>(2);


			//サポータと
			if (obj->GetObjType() == objType::Torch)
			{
				if (isHit()(Sspos, sSize, eSize))
				{
					//if (cntData[InputID::Btn1][static_cast<int>(Trg::Now)])
					{

						obj->moveStop_checkdie_flag = true;
						/*int ecSE = LoadSoundMem("image/SE/explosion.mp3");
						ChangeVolumeSoundMem(100, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);*/
					}
					continue;
				}
			}

			if (obj->GetObjType() == objType::Simultaneous)
			{
				if (isHit()(Sspos, sSize, eSize))
				{
					//if (cntData[InputID::Btn1][static_cast<int>(Trg::Now)])
					{
						obj->moveStop_checkdie_flag = true;
					}

					continue;
				}
			}
			Vector2Dbl pos1 = obj->pos_ + Vector2Dbl{ 20, 40 };
			Vector2Dbl epos1 = pos1 + ((obj->size_ - Vector2Dbl{ 40, 50 }) / half);
			Vector2Dbl eSize1 = (obj->size_ - Vector2Dbl{ 40, 50 }) / half;
			Vector2Dbl Sspos1 = epos1 - spos;
			if (obj->GetObjType() == objType::Door)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					int ecSE = LoadSoundMem("image/SE/robo.mp3");
					ChangeVolumeSoundMem(VolumeObjSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					moveStop_checkdie_flag = true;
				}
			}
			if (obj->GetObjType() == objType::DoorOpen)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					int ecSE = LoadSoundMem("image/SE/robo.mp3");
					ChangeVolumeSoundMem(VolumeObjSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					moveStop_checkdie_flag = true;
				}
			}
			//何かわからんけど、うまくいった
			if (obj->GetObjType() == objType::Pushbutton)
			{
				obj->moveStop_checkdie_flag = false;
				if (isHit()(Sspos, sSize, eSize))
				{
					obj->moveStop_checkdie_flag = true;
					cflag = true;
					continue;
				}

			}
			if (obj->GetObjType() == objType::PushDoor)
			{
				if (isHit()(Sspos1, sSize, eSize1))
				{
					int ecSE = LoadSoundMem("image/SE/robo.mp3");
					ChangeVolumeSoundMem(VolumeObjSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					moveStop_checkdie_flag = true;
				}
				if (cflag)
				{
					obj->moveStop_checkdie_flag = true;
					continue;
				}
				else
				{
					obj->moveStop_checkdie_flag = false;
					continue;
				}
			}


		}
		/*if (moveStop_checkdie_flag)
		{
			int ecSE = LoadSoundMem("image/SE/down.mp3");
			ChangeVolumeSoundMem(VolumeObjSE, ecSE);
			PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
		}*/
		return controller_;
	}
};