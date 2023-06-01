#include <DxLib.h>
#include "../common/imageMng.h"
#include "../Choice.h"
#include "../Input/KeyInput.h"
#include "../Input/imput_Scene/keyboard.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "HalfwayScene.h"
#include "Transition/CrossOver.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
SelectScene::SelectScene(UniqueInput& imput)
{
	Choice_ = Stage::zero;
	imput_ = std::move(imput);
	Init();
	DrawOwnScreen();
}
SelectScene::SelectScene(Stage Choice, Stagelist& Slist, UniqueInput& imput)
{
	ClearStagelist_ = std::move(Slist);
	/*ClearStagelist_.emplace_back(Stage::five);*/
	Choice_ = Choice;
	imput_ = std::move(imput);
	Init();
	DrawOwnScreen();
}

SelectScene::SelectScene(Stage Choice, Stagelist& Slist, Stagelist& OldSlist, UniqueInput& imput)
{

	OldClearStagelist_ = std::move(OldSlist);
	ClearStagelist_ = std::move(Slist);
	Choice_ = Choice;
	imput_ = std::move(imput);
	Init();
	DrawOwnScreen();
}

SelectScene::~SelectScene()
{
}

uniqueScene SelectScene::Update( uniqueScene ownScene)
{
	/*controller_ = std::make_unique<KeyInput>();*/

	imput_->Updata();
	auto& imputData = imput_->GetData(ImputType::NOW);
	auto& imputDataOld = imput_->GetData(ImputType::OLD);
	/*controller_->Updata();
	auto cntData = controller_->GetCntData();*/
	bool makeflag = false;
	if (!selectionFix_)
	{
		if (pageCnt_ > 1)
		{
			if (imputData.count("左") && imputDataOld.count("左"))
			{
				if (imputData.at("左") && !imputDataOld.at("左"))
				{
					pageCnt_--;
					alphaOnCnt_ = 0;
					MoveCnt_ = 0;
					OldClearStage_ = false;
							ChangeVolumeSoundMem(VolumeSE, ecSE);
							PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
				}
				if (imputData.at("左") && imputDataOld.at("左"))
				{
					alphaOnCnt_ = 0;
					if (MoveCnt_ >30)
					{

						if (MoveCnt_ % 40 == 0)
						{
							pageCnt_--;

							ChangeVolumeSoundMem(VolumeSE, ecSE);
							PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
						}
					}
					if (MoveCnt_ > 100)
					{
						if (MoveCnt_ % 20 == 0)
						{
							pageCnt_--;
							ChangeVolumeSoundMem(VolumeSE, ecSE);
							PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
						}
					}
					if (pageCnt_ < 1)
					{
						pageCnt_ = 1;
					}
					MoveCnt_++;
				}
				
					
				
			}
		}
		if (pageCnt_ < MaxpegeCnt_-1)
		{
			if (imputData.count("右") && imputDataOld.count("右"))
			{
				if (imputData.at("右") && !imputDataOld.at("右"))
				{
					pageCnt_++;
					alphaOnCnt_ = 0;
					MoveCnt_ = 0;
					OldClearStage_ = false;
					ChangeVolumeSoundMem(VolumeSE, ecSE);
					PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					/*	selectionPos_++;*/
				}
			}
			if (imputData.at("右") && imputDataOld.at("右"))
			{
				alphaOnCnt_ = 0;
				if (MoveCnt_ > 30)
				{

					if (MoveCnt_ % 40 == 0)
					{
						pageCnt_++;
						ChangeVolumeSoundMem(VolumeSE, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					}

				}
				if (MoveCnt_ > 100)
				{
					if (MoveCnt_ % 20 == 0)
					{
						pageCnt_++;
						ChangeVolumeSoundMem(VolumeSE, ecSE);
						PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
					}
				}
				if (pageCnt_ > MaxpegeCnt_ - 1)
				{
					pageCnt_ = MaxpegeCnt_ - 1;
				}
				MoveCnt_++;
			}
		}
	}
	//TRACE("%d\n", alphaOnCnt_);
	//ステージ選択
		//ステージセット
		//TRACE("%d\n", pageCnt_ + (pageCnt_Ten_ * 3));
	Choice_ = static_cast<Stage>(pageCnt_);
	selectnowmove_ = pos_.x *(static_cast<int>(Choice_) * 4);
	/*if (selectnowmove_ % pos_.x * (static_cast<int>(Choice_) * 4) == 0)
	{
		 
	}*/
	

	if (skipflag_)
	{
		if (imputData.count("A") && imputDataOld.count("A"))
		{
			if (imputData.at("A") && !imputDataOld.at("A"))
			{
				selectionPos_ = -screenSize_.y + 10;
				CenterMovestorage_.x = screenSize_.x / 2 - 100;
				CenterMovestorage_.y = screenSize_.y - 240;
				
			}
		}
	}
	if (imputData.count("A") && imputDataOld.count("A"))
	{
		if (imputData.at("A") && !imputDataOld.at("A"))
		{
			ChangeVolumeSoundMem(VolumeSE, ecS_);
			PlaySoundMem(ecS_, DX_PLAYTYPE_BACK, true);
			selectionMoveflag_ = true;
			selectionFix_ = true;
			
			if (selectionPos_ <= -screenSize_.y + 10)
			{

				ChangeVolumeSoundMem(VolumeSE, ec_);
				PlaySoundMem(ec_, DX_PLAYTYPE_BACK, true);
				if (!skipflag_)
				{
					makeflag = true;
				}

			}
			makeflag = true;
			skipflag_ = true;
		}
		
	}

	
	/*if (selectionMoveflag_)
	{
		if (selectionPos_ >= -screenSize_.y+10)
		{

			selectionPos_ -= selectionmove;
		}
		else
		{
			selectionMoveflag_ = false;
		}
	}*/
	if (makeflag)
	{
		//次のシーンに移行
		TRACE("GameSceneに移行\n");
		/*uniqueScene game = std::make_unique<GameScene>(Choice_, ClearStagelist_);*/
		return std::make_unique<CrossOver>(ownScene,std::make_unique<HalfwayScene>(Choice_, ClearStagelist_,imput_));
		/*return std::make_unique<GameScene>(Choice_);*/
	}
	/*if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (!CheckSoundMem(e_))
		{
			ChangeVolumeSoundMem(150, e_);
			PlaySoundMem(e_, DX_PLAYTYPE_BACK, true);
		}
		selectionFix_ = false;
		selectionMoveflag_ = false;
		MapUpBlendCnt_ = 0;
	}*/
	/*if (!selectionFix_)
	{
		if (selectionPos_ < 0)
		{
			selectionPos_ += selectionmove;
			
		}
	}*/
	if (ClearfadeinStartCnt_ > 20)
	{
		ClearfadeinGoflag_ = true;
	}
	
	DrawOwnScreen();
	animbuttonCnt_++;
	ClearfadeinStartCnt_++;
	return ownScene;
}

void SelectScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
	auto cnt = 7;
	auto offset = 20;
	
	DrawGraph(0, 0, lpImageMng.GetID("background.png")[0], true);
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);*/
	for (int j = 1; j < MaxpegeCnt_; j++)
	{
		smallsize_[j] = 100;
		if (static_cast<int>(Choice_) == j)
		{
			smallsize_[j] = 0;
		}
	}
	int ni = 300;
	int iiti = 200;//170
	int nono = /*324*/pos_.x * 4;
	int puss = 30;
	int haf = 24;
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 0+ haf) + smallsize_[1], static_cast<int>(iiti) + smallsize_[1], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 0) - smallsize_[1], (offset + 85 * 5.5 + puss) - smallsize_[1], lpImageMng.GetID("map1")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 1 + haf) + smallsize_[2], static_cast<int>(iiti) + smallsize_[2], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 1) - smallsize_[2], (offset + 85 * 5.5 + puss) - smallsize_[2], lpImageMng.GetID("map2")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 2 + haf) + smallsize_[3], static_cast<int>(iiti) + smallsize_[3], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 2) - smallsize_[3], (offset + 85 * 5.5 + puss) - smallsize_[3], lpImageMng.GetID("map3")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 3 + haf) + smallsize_[4], static_cast<int>(iiti) + smallsize_[4], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 3) - smallsize_[4], (offset + 85 * 5.5 + puss) - smallsize_[4], lpImageMng.GetID("map4")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 4 + haf) + smallsize_[5], static_cast<int>(iiti) + smallsize_[5], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 4) - smallsize_[5], (offset + 85 * 5.5 + puss) - smallsize_[5], lpImageMng.GetID("map5")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 5 + haf) + smallsize_[6], static_cast<int>(iiti) + smallsize_[6], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 5) - smallsize_[6], (offset + 85 * 5.5 + puss) - smallsize_[6], lpImageMng.GetID("map6")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 6 + haf) + smallsize_[7], static_cast<int>(iiti) + smallsize_[7], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 6) - smallsize_[7], (offset + 85 * 5.5 + puss) - smallsize_[7], lpImageMng.GetID("map7")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 7 + haf) + smallsize_[8], static_cast<int>(iiti) + smallsize_[8], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 7) - smallsize_[8], (offset + 85 * 5.5 + puss) - smallsize_[8], lpImageMng.GetID("map8")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 8 + haf) + smallsize_[9], static_cast<int>(iiti) + smallsize_[9], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 8) - smallsize_[9], (offset + 85 * 5.5 + puss) - smallsize_[9], lpImageMng.GetID("map9")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 9 + haf) + smallsize_[10], static_cast<int>(iiti) + smallsize_[10], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 9) - smallsize_[10], (offset + 85 * 5.5 + puss) - smallsize_[10], lpImageMng.GetID("map10")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 10 + haf) + smallsize_[11], static_cast<int>(iiti) + smallsize_[11], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 10) - smallsize_[11], (offset + 85 * 5.5 + puss) - smallsize_[11], lpImageMng.GetID("map11")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 11 + haf) + smallsize_[12], static_cast<int>(iiti) + smallsize_[12], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 11) - smallsize_[12], (offset + 85 * 5.5 + puss) - smallsize_[12], lpImageMng.GetID("map12")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 12 + haf) + smallsize_[13], static_cast<int>(iiti) + smallsize_[13], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 12) - smallsize_[13], (offset + 85 * 5.5 + puss) - smallsize_[13], lpImageMng.GetID("map13")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 13 + haf) + smallsize_[14], static_cast<int>(iiti) + smallsize_[14], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 13) - smallsize_[14], (offset + 85 * 5.5 + puss) - smallsize_[14], lpImageMng.GetID("map14")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 14 + haf) + smallsize_[15], static_cast<int>(iiti) + smallsize_[15], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 14) - smallsize_[15], (offset + 85 * 5.5 + puss) - smallsize_[15], lpImageMng.GetID("map15")[0], true);
	DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 15 + haf) + smallsize_[16], static_cast<int>(iiti) + smallsize_[16], (static_cast<int>(screenSize_.x - ni) - selectnowmove_ + nono + nono * 15) - smallsize_[16], (offset + 85 * 5.5 + puss) - smallsize_[16], lpImageMng.GetID("map16")[0], true);

	
	if (ClearStagelist_.empty())
	{
		//クリア下ステージがなかったら、普通に描画
		DrawExtendGraph(static_cast<int>(60 * 2),
			static_cast<int>(96),
			static_cast<int>(screenSize_.x - 60 * 2),
			static_cast<int>(offset + 85 * 7), lpImageMng.GetID("oldmapflame.png")[0], true);
	}
	else
	{
		
		int con = 0;
		for (auto clear : ClearStagelist_)
		{
			
			//選んでるステージとクリアしたことあるステージを比べて
			//クリアしていれば描画を変える
			if (static_cast<int>(Choice_) == static_cast<int>(clear))
			{
				
				if (ClearfadeinGoflag_)
				{
					//α増加開始
					ClearfadeinCnt_+=2;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ClearfadeinCnt_);
				DrawExtendGraph(static_cast<int>(60 * 2),
					static_cast<int>(96),
					static_cast<int>(screenSize_.x - 60 * 2),
					static_cast<int>(offset + 85 * 7), lpImageMng.GetID("Clearmapflame.png")[0], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
				//アニメーション時にボタンのアニメーションを止める
				if (ClearfadeinCnt_ < 255)
				{
					alphaOnCnt_ = 0;
				}
				//下のflameをαをつけるかつけないかしている
				if (con > 0)
				{
					//もともとクリアしていたら
					//fadeinせずに普通に描画
					OldClearStage_ = true;
				}
				else
				{
					// 初めてクリアしたステージfadeoutする
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - ClearfadeinCnt_);

				}
				con++;
			}
			
				
			
		}
		if (OldClearStage_)
		{
			//クリアしたことあるステージは普通に描画
			DrawExtendGraph(static_cast<int>(60 * 2),
				static_cast<int>(96),
				static_cast<int>(screenSize_.x - 60 * 2),
				static_cast<int>(offset + 85 * 7), lpImageMng.GetID("Clearmapflame.png")[0], true);
		}
		else
		{
			//クリアしたことないステージだった時の描画	
			DrawExtendGraph(static_cast<int>(60 * 2),
				static_cast<int>(96),
				static_cast<int>(screenSize_.x - 60 * 2),
				static_cast<int>(offset + 85 * 7), lpImageMng.GetID("oldmapflame.png")[0], true);
		}
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

	//選択の光
	int add = 70;
	DrawExtendGraph(pos_.x + pos_.x * 3+ haf,
		pos_.y + selectionPos_+ add,
		static_cast<int>((pos_.x) + 170) + pos_.x * 3+ haf,
		static_cast<int>(pos_.y + 85) + selectionPos_+ add, lpImageMng.GetID("unnamed.png")[0], true);

	alphaOnCnt_++;
	if (alphaOnCnt_ > 20)
	{
		alphaCnt_++;
	}
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
	//タイトルの囲ってる緑
	DrawExtendGraph(static_cast<int>(20),
		static_cast<int>(70 + 5) + selectionPos_,
		static_cast<int>(1024 - 20),
		static_cast<int>(96 + 70 - 5) + selectionPos_, lpImageMng.GetID("stageframe.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	//タイトルの緑の上にある黒い枠
	DrawExtendGraph(static_cast<int>(0),
		static_cast<int>(70),
		static_cast<int>(screenSize_.x),
		static_cast<int>(96 + 70) , lpImageMng.GetID("horror2.png")[0], true);
	//タイトル
	DrawGraph(screenSize_.x /2-60*3, 90 , lpImageMng.GetID("stage.png")[0], true);
	//下の枠
	DrawExtendGraph(static_cast<int>(-30),
		static_cast<int>(680),
		static_cast<int>(screenSize_ .x+30),
		static_cast<int>(680 + 96), lpImageMng.GetID("syber2mini.png")[0], true);
	int sizebut = 44;
	DrawGraph(screenSize_.x - 60 * 2 - sizebut * 5, screenSize_.y - 65 , lpImageMng.GetID("buttonZ.png")[alphaCnt_ / 30 % 2], true);
	DrawGraph(screenSize_.x - 60 * 2 - sizebut *4, screenSize_.y - 65 , lpImageMng.GetID("Decision.png")[0], true);
	int sizemove = 50;
	DrawGraph(60 * 2 + sizemove - (animbuttonCnt_ / 40 % 2), screenSize_.y - 65, lpImageMng.GetID("leftbutton.png")[0], true);
	DrawGraph(60 * 2 + sizemove * 2 + (animbuttonCnt_ / 40 % 2), screenSize_.y - 65, lpImageMng.GetID("rightbutton.png")[0], true);
	DrawGraph(60 * 2 + sizemove * 3, screenSize_.y - 65, lpImageMng.GetID("move.png")[0], true);
	Vector2 buttonOffset = {57,30};
	for (int j = 1; j < MaxpegeCnt_; j++)
	{
		if (j >= 10)
		{
			buttonOffset.x = 52;
		}
		bool clearframeflag = false;
		for (auto clear : ClearStagelist_)
		{
			if (j == static_cast<int>(clear))
			{
				clearframeflag = true;
			}
		}
		/*if (static_cast<int>(Choice_) == j)*/
		//{
			/*if (!selectionFix_)
			{
				continue;
			}*/
			CenterMovestorage_ = { pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4 + haf , pos_.y + add };
			if (clearframeflag)
			{
				//クリアステージのボタン変更
				//ステージのボタン
				//星マークつきのフレームに変更予定
				DrawGraph(CenterMovestorage_.x, CenterMovestorage_.y, lpImageMng.GetID("frame.png")[0], true);
				//クリア下ステージのバッチ描画
				/*if (!OldClearStage_)
				{
					if (ClearfadeinCnt_ > 255)
					{

						inbatchCnt_++;
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, inbatchCnt_);
						DrawExtendGraph(static_cast<int>(pos_.x* (j * 4) - selectnowmove_ + pos_.x * 4 + 50),
							pos_.y + 100 + add + 20,
							static_cast<int>(pos_.x* (j * 4) - selectnowmove_ + pos_.x * 4 + ExpSize + 50),
							static_cast<int>(pos_.y + 100 + add + ExpSize + 20), lpImageMng.GetID("batch.png")[0], true);
					}
					
				}
				else
				{
					DrawExtendGraph(static_cast<int>(pos_.x* (j * 4) - selectnowmove_ + pos_.x * 4 + 50),
						pos_.y + 100 + add + 20,
						static_cast<int>(pos_.x* (j * 4) - selectnowmove_ + pos_.x * 4 + ExpSize + 50),
						static_cast<int>(pos_.y + 100 + add + ExpSize + 20), lpImageMng.GetID("batch.png")[0], true);
				}*/
					
				
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
			else
			{
				//ステージのボタン
				DrawGraph(CenterMovestorage_.x, CenterMovestorage_.y, lpImageMng.GetID("frame.png")[cnt], true);
			}
			//ステージ名
			DrawGraph(buttonOffset.x + pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4, buttonOffset.y + pos_.y + selectionPos_ + add, lpImageMng.GetID("stage")[j-1], true);
			//else
			//{
			//	/*if (static_cast<int>(Choice_) % 3 == 0)
			//	{
			//		if (CenterMovestorage_.x >= screenSize_.x / 2 - 100)
			//		{
			//			CenterMovestorage_.x -= selectionmove;
			//		}
			//	}
			//	else
			//	{
			//		if (CenterMovestorage_.x <= screenSize_.x / 2 - 100)
			//		{
			//			CenterMovestorage_.x += selectionmove;
			//		}
			//	}*/
			//	/*if (CenterMovestorage_.y <= screenSize_.y - 240)
			//	{
			//		CenterMovestorage_.y += selectionmove;
			//	}*/
			//	//ステージのボタン
			//	DrawGraph(CenterMovestorage_.x, CenterMovestorage_.y, lpImageMng.GetID("frame.png")[cnt], true);
			//	//ステージ名
			//	DrawGraph(buttonOffset.x + pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4, buttonOffset.y + pos_.y + selectionPos_ + add, lpImageMng.GetID("stage")[j - 1], true);
			//
			//}

		//}
		//else
		//{
		//	//選択していないステージボタンの表示
		//	//表示してもしなくてもいい
		//	//ステージのボタン
		//	DrawGraph((pos_.x * (j * 4) - selectnowmove_) + pos_.x * 4+ haf, pos_.y + selectionPos_ + add, lpImageMng.GetID("frame.png")[cnt], true);
		//	//ステージ名
		//	DrawGraph(buttonOffset.x + pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4, buttonOffset.y + pos_.y + selectionPos_ + add, lpImageMng.GetID("stage")[j - 1], true);

		//}
	}
	
	//ステージのマップ
	if (ClearfadeinCnt_ != 0 && ClearfadeinCnt_ < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,200);
	}
	switch (Choice_)
	{
	case Stage::one:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 0 + haf) + smallsize_[1], static_cast<int>(iiti) + smallsize_[1], (static_cast<int>(screenSize_.x - ni+ haf) - selectnowmove_ + nono + nono * 0) - smallsize_[1], (offset + 85 * 5.5 + puss) - smallsize_[1], lpImageMng.GetID("map1")[0], true);

		break;
	case Stage::two:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 1 + haf) + smallsize_[2], static_cast<int>(iiti) + smallsize_[2], (static_cast<int>(screenSize_.x - ni+ haf) - selectnowmove_ + nono + nono * 1) - smallsize_[2], (offset + 85 * 5.5 + puss) - smallsize_[2], lpImageMng.GetID("map2")[0], true);

		break;
	case Stage::three:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 2 + haf) + smallsize_[3], static_cast<int>(iiti) + smallsize_[3], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 2) - smallsize_[3], (offset + 85 * 5.5 + puss) - smallsize_[3], lpImageMng.GetID("map3")[0], true);

		break;
	case Stage::four:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 3 + haf) + smallsize_[4], static_cast<int>(iiti) + smallsize_[4], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 3) - smallsize_[4], (offset + 85 * 5.5 + puss) - smallsize_[4], lpImageMng.GetID("map4")[0], true);

		break;
	case Stage::five:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 4 + haf) + smallsize_[5], static_cast<int>(iiti) + smallsize_[5], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 4) - smallsize_[5], (offset + 85 * 5.5 + puss) - smallsize_[5], lpImageMng.GetID("map5")[0], true);

		break;
	case Stage::six:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 5 + haf) + smallsize_[6], static_cast<int>(iiti) + smallsize_[6], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 5) - smallsize_[6], (offset + 85 * 5.5 + puss) - smallsize_[6], lpImageMng.GetID("map6")[0], true);

		break;
	case Stage::seven:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 6 + haf) + smallsize_[7], static_cast<int>(iiti) + smallsize_[7], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 6) - smallsize_[7], (offset + 85 * 5.5 + puss) - smallsize_[7], lpImageMng.GetID("map7")[0], true);

		break;
	case Stage::eight:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 7 + haf) + smallsize_[8], static_cast<int>(iiti) + smallsize_[8], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 7) - smallsize_[8], (offset + 85 * 5.5 + puss) - smallsize_[8], lpImageMng.GetID("map8")[0], true);

		break;
	case Stage::nine:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 8 + haf) + smallsize_[9], static_cast<int>(iiti) + smallsize_[9], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 8) - smallsize_[9], (offset + 85 * 5.5 + puss) - smallsize_[9], lpImageMng.GetID("map9")[0], true);

		break;
	case Stage::ten:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 9 + haf) + smallsize_[10], static_cast<int>(iiti) + smallsize_[10], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 9) - smallsize_[10], (offset + 85 * 5.5 + puss) - smallsize_[10], lpImageMng.GetID("map10")[0], true);

		break;
	case Stage::eleven:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 10 + haf) + smallsize_[11], static_cast<int>(iiti) + smallsize_[11], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 10) - smallsize_[11], (offset + 85 * 5.5 + puss) - smallsize_[11], lpImageMng.GetID("map11")[0], true);

		break;
	case Stage::twelve:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 11 + haf) + smallsize_[12], static_cast<int>(iiti) + smallsize_[12], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 11) - smallsize_[12], (offset + 85 * 5.5 + puss) - smallsize_[12], lpImageMng.GetID("map12")[0], true);

		break;
	case Stage::thirteen:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 12 + haf) + smallsize_[13], static_cast<int>(iiti) + smallsize_[13], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 12) - smallsize_[13], (offset + 85 * 5.5 + puss) - smallsize_[13], lpImageMng.GetID("map13")[0], true);

		break;
	case Stage::fourteen:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 13 + haf) + smallsize_[14], static_cast<int>(iiti) + smallsize_[14], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 13) - smallsize_[14], (offset + 85 * 5.5 + puss) - smallsize_[14], lpImageMng.GetID("map14")[0], true);

		break;
	case Stage::fifteen:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 14 + haf) + smallsize_[15], static_cast<int>(iiti) + smallsize_[15], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 14) - smallsize_[15], (offset + 85 * 5.5 + puss) - smallsize_[15], lpImageMng.GetID("map15")[0], true);

		break;
	case Stage::sixteen:
		DrawExtendGraph((static_cast<int>(screenSize_.x / 4) - selectnowmove_ + nono + nono * 15 + haf) + smallsize_[16], static_cast<int>(iiti) + smallsize_[16], (static_cast<int>(screenSize_.x - ni + haf) - selectnowmove_ + nono + nono * 15) - smallsize_[16], (offset + 85 * 5.5 + puss) - smallsize_[16], lpImageMng.GetID("map16")[0], true);

		break;
	default:
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	//DrawExtendGraph(static_cast<int>(1024 / 4 ) - selectnowmove_ + pos_.x * 4 + nono * 0, static_cast<int>(iiti), static_cast<int>(1024 - ni) - selectnowmove_ + pos_.x * 4 + nono * 0, static_cast<int>(offset + 85 * 5.5), lpImageMng.GetID("map1")[0], true);
	//DrawExtendGraph((static_cast<int>(1024 / 4 ) - selectnowmove_ + nono + nono * 14)+ smallsize_[15], static_cast<int>(iiti)+ smallsize_[15], (static_cast<int>(1024 - ni) - selectnowmove_ + nono + nono * 14 )- smallsize_[15], (offset + 85 * 5.5 + puss) - smallsize_[15], lpImageMng.GetID("map15")[0], true);
	//DrawExtendGraph((static_cast<int>(1024 / 4 ) - selectnowmove_ + nono + nono * 15)+ smallsize_[16], static_cast<int>(iiti)+ smallsize_[16], (static_cast<int>(1024 - ni) - selectnowmove_ + nono + nono * 15 )- smallsize_[16], (offset + 85 * 5.5 + puss) - smallsize_[16], lpImageMng.GetID("map16")[0], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (alphaCnt_ * 4) % 255);
	DrawGraph(pos_.x * 4+ haf, pos_.y + selectionPos_+ add, lpImageMng.GetID("frame.png")[4], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

	for (int j = 1; j < MaxpegeCnt_; j++)
	{
		bool Oldstage = false;
		for (auto clear : ClearStagelist_)
		{
			if (j == static_cast<int>(clear))
			{
				for (auto Oldclear : OldClearStagelist_)
				{
					if (clear == Oldclear)
					{
						if (static_cast<int>(Choice_) != static_cast<int>(clear))
						{

							Oldstage = true;
						}
						
					}
				}
				int clearoffset = 1;
				//クリア下ステージのバッチ描画
				int collor = 6;
				if (!Oldstage)
				{
					if (ClearfadeinCnt_ > 255)
					{
						int alcnt;
						
						//色試し変更
						//int alcnt = collor*3+2;
						//アニメーション時にボタンのアニメーションを止める
						if (inbatchCnt_ < 255)
						{
							alphaOnCnt_ = 0;
							alcnt = (inbatchCnt_ / (255/3) % 3) + collor * 3;
						}
						else
						{
							alcnt = collor * 3 + 2;
						}
						
						inbatchCnt_++;
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, inbatchCnt_);
						DrawGraph(pos_.x * (j * 4) + haf - selectnowmove_+ pos_.x * 4- clearoffset,
							pos_.y + selectionPos_ + add- clearoffset,
							lpImageMng.GetID("starC.png")[alcnt], true);
						
						/*DrawExtendGraph(static_cast<int>(pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4 + 50),
							pos_.y + 100 + add + 20,
							static_cast<int>(pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4 + ExpSize + 50),
							static_cast<int>(pos_.y + 100 + add + ExpSize + 20), lpImageMng.GetID("starC.png")[5], true);*/
					}

				}
				else
				{
					DrawGraph(pos_.x * (j*4) + haf - selectnowmove_ + pos_.x * 4- clearoffset, pos_.y + selectionPos_ + add- clearoffset, lpImageMng.GetID("starC.png")[collor * 3 + 2], true);

					/*DrawExtendGraph(static_cast<int>(pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4 + 50),
						pos_.y + 100 + add + 20,
						static_cast<int>(pos_.x * (j * 4) - selectnowmove_ + pos_.x * 4 + ExpSize + 50),
						static_cast<int>(pos_.y + 100 + add + ExpSize + 20), lpImageMng.GetID("starC.png")[5], true);*/
				}


				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
		}
	}
	/*if (CenterMovestorage_.y > screenSize_.y - 240)
	{

		DrawGraph(offset + CenterMovestorage_.x, offset + CenterMovestorage_.y, lpImageMng.GetID("stage")[static_cast<int>(Choice_) - 1], true);
	}*/
}

bool SelectScene::Init(void)
{
	/*Choice_ = Choice::zero;*/
	pos_ = {100,500};
	selectionPos_ = 0;
	pageCnt_ = 1;
	if (Choice_ != Stage::zero)
	{
		pageCnt_ = static_cast<int>(Choice_);
	}
	pageCnt_Ten_ = 0;
	alphaCnt_ = 0;
	alphaOnCnt_ = 0;
	MapUpBlendCnt_ = 0;
	selectionMoveflag_ = false;
	selectionFix_ = false;
	skipflag_ = false;
	selectnowmove_ = 0;
	MaxpegeCnt_ = 17;
	MoveCnt_ = 0;
	ClearfadeinCnt_ = 0;
	ClearfadeinStartCnt_ = 0;
	ClearfadeinGoflag_ = false;
	OldClearStage_ = false;
	for (int x = 1; x < MaxpegeCnt_; x++)
	{
		smallsize_[x] = ExpSize;
	}
	/*imput_ = std::make_unique<keyboard>();*/
	lpImageMng.GetID("image/select/frameC.png", "frame.png", {170,85}, {2,4});
	lpImageMng.GetID("image/background.png", "background.png");
	lpImageMng.GetID("image/select/stage.png", "stage.png");
	lpImageMng.GetID("image/syber2mini.png", "syber2mini.png");
	lpImageMng.GetID("image/select/stageframe.png", "stageframe.png");
	lpImageMng.GetID("image/tegami_mini2.png", "horror2.png");
	lpImageMng.GetID("image/unnamed.png", "unnamed.png");
	//lpImageMng.GetID("image/Spacebutton.png", "Spacebutton.png", {100,50}, {2,1});
	lpImageMng.GetID("image/select/Decision.png", "Decision.png");
	lpImageMng.GetID("image/selectmap/selectmap1.png","map1"); 
	lpImageMng.GetID("image/selectmap/selectmap2.png", "map2");
	lpImageMng.GetID("image/selectmap/selectmap3.png", "map3");
	lpImageMng.GetID("image/selectmap/selectmap4.png", "map4");
	lpImageMng.GetID("image/selectmap/selectmap5.png", "map5");
	lpImageMng.GetID("image/selectmap/selectmap6.png", "map6");
	lpImageMng.GetID("image/selectmap/selectmap7.png", "map7");
	lpImageMng.GetID("image/selectmap/selectmap8.png", "map8");
	lpImageMng.GetID("image/selectmap/selectmap9.png", "map9");
	lpImageMng.GetID("image/selectmap/selectmap10.png", "map10");
	lpImageMng.GetID("image/selectmap/selectmap11.png", "map11");
	lpImageMng.GetID("image/selectmap/selectmap12.png", "map12");
	lpImageMng.GetID("image/selectmap/selectmap13.png", "map13");
	lpImageMng.GetID("image/selectmap/selectmap14.png", "map14");
	lpImageMng.GetID("image/selectmap/selectmap15.png", "map15");
	lpImageMng.GetID("image/selectmap/selectmap16.png", "map16");
	lpImageMng.GetID("image/selectmap/selectlogo/stage.png", "stage", {120,24}, {1,MaxpegeCnt_ -1});
	lpImageMng.GetID("image/select/oldmapflame.png", "oldmapflame.png");
	lpImageMng.GetID("image/select/Clearmapflame.png", "Clearmapflame.png");

	lpImageMng.GetID("image/cancel.png", "cancel.png");
	lpImageMng.GetID("image/Esc.png", "Esc.png");
	lpImageMng.GetID("image/batch.png", "batch.png");

	lpImageMng.GetID("image/select/leftbutton.png", "leftbutton.png");
	lpImageMng.GetID("image/select/rightbutton.png", "rightbutton.png");
	lpImageMng.GetID("image/select/move.png", "move.png");
	lpImageMng.GetID("image/select/starC.png", "starC.png", {24,24} ,{3,10});

	ecSE = LoadSoundMem("image/SE/select.mp3");
	ecS_ = LoadSoundMem("image/SE/clicksele.mp3");
	ec_ = LoadSoundMem("image/SE/titleclick.mp3");
	e_ = LoadSoundMem("image/SE/cancel.mp3");
	return true;
}
