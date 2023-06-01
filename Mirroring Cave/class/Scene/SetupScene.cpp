#include <DxLib.h>
#include "../common/imageMng.h"

#include "GameScene.h"
#include "SetupScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "HalfwayScene.h"
#include "../Input/imput_Scene/keyboard.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

SetupScene::SetupScene()
{
	Init();
	DrawOwnScreen();
}
SetupScene::SetupScene(Stage Choice , Stagelist& Slist, uniqueScene& ownScene, int RECnt)
{
	ClearStagelist_ = std::move(Slist);
	ownScene_ = std::move(ownScene);
	Choice_ = Choice;
	Tipsflag_ = false;
	//Tips_ = Tips;
	RECnt_ = RECnt;
	//lpImageMng.GetID(Tips_);
	Init();
	DrawOwnScreen();
}

SetupScene::~SetupScene()
{
}

uniqueScene SetupScene::Update( uniqueScene ownScene)
{

	imput_->Updata();
	auto& imputData = imput_->GetData(ImputType::NOW);
	auto& imputDataOld = imput_->GetData(ImputType::OLD);
	bool makeflag = false;
	
	if (pageCnt_ > 0)
	{
		if (imputData.count("上") && imputDataOld.count("上"))
		{
			if (imputData.at("上") && !imputDataOld.at("上"))
			{
				pageCnt_--;
				ChangeVolumeSoundMem(VolumeSE, ecSE);
				PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
				DecisionCnt_++;
			}
		}
	}
	if (pageCnt_ < static_cast<int>(NextSceneChoice::Max)-2)
	{
		if (imputData.count("下") && imputDataOld.count("下"))
		{
			if (imputData.at("下") && !imputDataOld.at("下"))
			{
				pageCnt_++;
				ChangeVolumeSoundMem(VolumeSE, ecSE);
				PlaySoundMem(ecSE, DX_PLAYTYPE_BACK, true);
				DecisionCnt_++;

			}
		}
	}

	//ステージ選択
	NextChoice_ = static_cast<NextSceneChoice>(pageCnt_);
	if (imputData.count("A") && imputDataOld.count("A"))
	{
		if (imputData.at("A") && !imputDataOld.at("A"))
		{
			ChangeVolumeSoundMem(VolumeSE, ec_);
			PlaySoundMem(ec_, DX_PLAYTYPE_BACK, true);
			switch (NextChoice_)
			{
			case NextSceneChoice::Gamereturn:
				//ゲームを続ける際
				StartTime_ = 
				//TRACE("GameSceneに移行\n");
				ChangeVolumeSoundMem(VolumeSE, ecS_);
				PlaySoundMem(ecS_, DX_PLAYTYPE_BACK, true);
				return std::move(ownScene_); 
				break;
			case NextSceneChoice::Restart:
				//リセットする際
				RECnt_++;
				return std::make_unique<HalfwayScene>(Choice_, ClearStagelist_, RECnt_, imput_);
				break;
			case NextSceneChoice::Select:
				return std::make_unique<SelectScene>(Choice_, ClearStagelist_,imput_);
				break;
			case NextSceneChoice::Title:
				return std::make_unique<TitleScene>(imput_);
				break;
			case NextSceneChoice::Tips:
				//ヒントを表示する
				//Tipsflag_ = true;
				break;
			}
		}
	}

	DrawOwnScreen();
	Cnt_++;
	if ((screenSize_.x - ChipSize * 6)>DrawAnimCnt_)
	{
		DrawAnimCnt_+=32;
		//DrawAnimCnt_ += 8;
		
	}
	else
	{
		fontDrawflag_ = true;
	}

	return ownScene;
}

void SetupScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	ownScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	/*DrawFormatString(0,0,0xffffff,"SetupScene\n");*/
	//int offset = 20;
	int centersize = 35;
	int centersizese = 88;

	DrawExtendGraph(static_cast<int>(ChipSize *6), static_cast<int>(screenSize_.y/2- slide_move_size*3+10), static_cast<int>(DrawAnimCnt_/*screenSize_.x-ChipSize *6*/), static_cast<int>(screenSize_.y / 2 + slide_move_size * 2.5), lpImageMng.GetID("syber1mini.png")[0], true);//syber2mini
	if (fontDrawflag_)
	{
		DrawGraph(screenSize_.x / 2 - centersize * 2, screenSize_.y / 2 - slide_move_size * 2 - 2, lpImageMng.GetID("gamereturn.png")[0], true);
		DrawGraph(screenSize_.x / 2 - centersizese + 5, screenSize_.y / 2 - slide_move_size, lpImageMng.GetID("restart.png")[0], true);
		DrawGraph(screenSize_.x / 2 - centersizese, screenSize_.y / 2, lpImageMng.GetID("select.png")[0], true);
		/*DrawGraph(pos_.x + point_offset, pos_.y + offset + slide_move_size * 3, lpImageMng.GetID("set.png")[0], true);*/
		DrawGraph(screenSize_.x / 2 - centersizese, screenSize_.y / 2 + slide_move_size, lpImageMng.GetID("title.png")[0], true);
		//DrawGraph(pos_.x + point_offset, pos_.y + offset + slide_move_size * 4 , lpImageMng.GetID("tips.png")[0], true);

		DrawGraph(pos_.x + slide_move_size * 2 + (Cnt_ / 10 % 5), screenSize_.y / 2 - slide_move_size * 2.2 + (slide_move_size * pageCnt_), lpImageMng.GetID("Arrow.png")[0], true);
		//if (Tipsflag_)
		//{
			////どのヒントを表示するのか
			//if (Choice_ == Choice::one)
			//{
			//	/*TRACE("%d\n", Tips_);*/
			//	DrawGraph(0, 0, lpImageMng.GetID(Tips_)[0], true);
			//}
			//if (Choice_ == Choice::two)
			//{
			//	DrawGraph(0, 0, lpImageMng.GetID(Tips_)[0], true);
			//}
			//if (Choice_ == Choice::three)
			//{
			//	DrawGraph(0, 0, lpImageMng.GetID(Tips_)[0], true);
			//}
		//}
		
			DrawGraph(screenSize_.x / 2 + 30 + ChipSize, screenSize_.y - 240, lpImageMng.GetID("buttonZ.png")[DecisionCnt_%2], true);
			DrawGraph(screenSize_.x / 2 + 80 + ChipSize, screenSize_.y - 240, lpImageMng.GetID("Decision.png")[0], true);
		
	}
}

bool SetupScene::Init(void)
{
	Cnt_ = 0;
	DrawAnimCnt_ = ChipSize * 6; 
	fontDrawflag_ = false;
	DecisionCnt_ = 0;
	lpImageMng.GetID("image/Arrow.png", "Arrow.png");
	lpImageMng.GetID("image/logo/gamereturn.png", "gamereturn.png");
	lpImageMng.GetID("image/logo/restart.png", "restart.png");
	lpImageMng.GetID("image/logo/select.png", "select.png");
	lpImageMng.GetID("image/logo/title.png", "title.png");
	lpImageMng.GetID("image/logo/tips.png", "tips.png");
	lpImageMng.GetID("image/tegami1.png", "tegami1.png");
	lpImageMng.GetID("image/ant1.png", "syber1mini.png");
	imput_ = std::make_unique<keyboard>();
	pos_ = { screenSize_.x/4,screenSize_ .y/5};
	ecSE = LoadSoundMem("image/SE/select.mp3");
	ecS_ = LoadSoundMem("image/SE/cancel.mp3");
	ec_ = LoadSoundMem("image/SE/titleclick.mp3");
	eccSE_ = LoadSoundMem("image/SE/setupgo.mp3");

	ChangeVolumeSoundMem(VolumeSE, eccSE_);
	PlaySoundMem(eccSE_, DX_PLAYTYPE_BACK, true);
	
	return true;
}
