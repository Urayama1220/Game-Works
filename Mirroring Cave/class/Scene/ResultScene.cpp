#include <DxLib.h>
#include "../common/imageMng.h"

#include "SelectScene.h"
#include "ResultScene.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
ResultScene::ResultScene()
{
	Init();
	DrawOwnScreen();
}

ResultScene::ResultScene(Stage Choice, Stagelist& Slist, int time, int RECnt, UniqueInput& imput)
{
	ClearStagelist_ = std::move(Slist);
	imput_ = std::move(imput);
	Choice_ = Choice;
	GemeTime_ = time;
	RECnt_ = RECnt;
	Init();
	DrawOwnScreen();
}

ResultScene::~ResultScene()
{
}

uniqueScene ResultScene::Update( uniqueScene ownScene)
{
	imput_->Updata();
	auto& imputData = imput_->GetData(ImputType::NOW);
	auto& imputDataOld = imput_->GetData(ImputType::OLD);
	if (imputData.count("A") && imputDataOld.count("A"))
	{
		if (imputData.at("A") && !imputDataOld.at("A"))
		{
			//次のシーンに移行
			TRACE("selectに移行\n");
			ChangeVolumeSoundMem(VolumeSE, eSE_);
			PlaySoundMem(eSE_, DX_PLAYTYPE_BACK, true);
			OldClearStagelist_ = ClearStagelist_;
			ClearStagelist_.emplace_back(Choice_);
			return std::make_unique<SelectScene>(Choice_, ClearStagelist_, OldClearStagelist_,imput_);
		}
	}
	gemaclearCnt_ +=2;
	if (gemaclearCnt_move_<=20)
	{
		gemaclearCnt_move_++;
	}
	if (gemaclearCnt_ >200)
	{
		/*curtainCnt_.x+=2;*/
		if (curtainCnt_.y < 96 + ResultfontOffsetY * 7)
		{
			curtainCnt_.y += 8;
			if (!CheckSoundMem(eccSE_))
			{
				ChangeVolumeSoundMem(VolumeSE, eccSE_);
				PlaySoundMem(eccSE_, DX_PLAYTYPE_BACK, true);
			}
		}
		
	}
	if (curtainCnt_.y>= 96 + ResultfontOffsetY * 7)
	{
		DrawResultflag_ = true;
	}
	Timecnt_++;
	DrawOwnScreen();
	return ownScene;
	
}

void ResultScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawExtendGraph(0, 0, screenSize_.x, screenSize_.y, lpImageMng.GetID("Visiblelight.png")[0], true);

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	///*ownScene_->Draw();*/
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	/*SetDrawBlendMode(DX_BLENDMODE_MULA, 200);*/
	/*DrawExtendGraph(static_cast<int>( 120), static_cast<int>(70), static_cast<int>(1024-120), static_cast<int>(96 + 70), lpImageMng.GetID("syber2mini.png")[0], true);*/
	/*DrawBox(static_cast<int>(120), static_cast<int>(70), static_cast<int>(screenSize_.x / 2 + 40 * 9), static_cast<int>(96 + 88 * 7),0x444444, true);*/
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BLEND_NOBLEND);
	DrawExtendGraph(static_cast<int>(ChipSize * 3), static_cast<int>(70), static_cast<int>(screenSize_.x - (ChipSize * 3)), static_cast<int>(curtainCnt_.y), lpImageMng.GetID("horror2.png")[0], true);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, gemaclearCnt_);
	DrawGraph(1024 / 4+10,  96-20+ gemaclearCnt_move_, lpImageMng.GetID("clear.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BLEND_NOBLEND);

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	//DrawBox(screenSize_.x / 2 - 40 * 7, 88 * 2.25, screenSize_.x / 2 + 40 * 6, 88 * 7, 0x666666, true);
	if (DrawResultflag_)
	{
		DrawResultCnt_ += 4;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, DrawResultCnt_);
		DrawExtendGraph(static_cast<int>(ChipSize * 5), static_cast<int>(ResultfontOffsetY * 2), static_cast<int>(screenSize_.x - (ChipSize * 5)), static_cast<int>(ResultfontOffsetY * 7.2), lpImageMng.GetID("syber2mini.png")[0], true);
		
		int resultadapt = 15;
		int cleartimeYOffset = 66;
		int result = 10;
		DrawGraph(screenSize_.x / 2 - 63 * 2, ResultfontOffsetY * 2 + result, lpImageMng.GetID("result.png")[0], true);
		DrawGraph(screenSize_.x / 2 - fontHalfSizeX * 3, ResultfontOffsetY * 3 + 25, lpImageMng.GetID("NumberResets.png")[0], true);
		DrawGraph(screenSize_.x / 2 + fontHalfSizeX * 2 + RestartOffset_, ResultfontOffsetY * 4, lpImageMng.GetID("kai.png")[0], true);
		DrawGraph(screenSize_.x / 2 - fontHalfSizeX * 3, ResultfontOffsetY * 4 + cleartimeYOffset, lpImageMng.GetID("Cleartime.png")[0], true);
		//DrawGraph(screenSize_.x / 2 + fontHalfSizeX * 2 + TimeOffset_, ResultfontOffsetY * 6 - resultadapt - NumberAdapt_, lpImageMng.GetID("Seconds.png")[0], true);

		DrawGraph(screenSize_.x / 2, ResultfontOffsetY * 7.5, lpImageMng.GetID("buttonZ.png")[Timecnt_ / 20 % 2], true);
		DrawGraph(screenSize_.x / 2 + fontHalfSizeX * 1, ResultfontOffsetY * 7.5, lpImageMng.GetID("StageSelection.png")[0], true);
		DrawTimer(GemeTime_ / 1000.0f);
		DrawRestart();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BLEND_NOBLEND);
	}

}

bool ResultScene::Init(void)
{
	lpImageMng.GetID("image/logo/clear1.png", "clear.png");
	lpImageMng.GetID("image/logo/Cleartime.png", "Cleartime.png");
	lpImageMng.GetID("image/logo/NumberResets.png", "NumberResets.png");
	lpImageMng.GetID("image/logo/result1.png", "result.png");
	lpImageMng.GetID("image/logo/StageSelection.png", "StageSelection.png"); 
	lpImageMng.GetID("image/logo/Seconds.png", "Seconds.png");
	lpImageMng.GetID("image/logo/kai.png", "kai.png");
	lpImageMng.GetID("image/Visiblelight.png", "Visiblelight.png");
	int ecS_ = LoadSoundMem("image/SE/clicksele.mp3");
	ChangeVolumeSoundMem(VolumeSE, ecS_);
	PlaySoundMem(ecS_, DX_PLAYTYPE_BACK, true);

	eSE_ = LoadSoundMem("image/SE/clicksele.mp3");

	eccSE_ = LoadSoundMem("image/SE/reSE.mp3");

	
	TimeOffset_ = 72;
	RestartOffset_ = 30;
	NumberAdapt_ = 40;
	gemaclearCnt_ = 0;
	curtainCnt_ = {0,70};
	DrawResultCnt_ = 0;
	gemaclearCnt_move_ = 0;
	DrawResultflag_ = false;
	return true;
}
void ResultScene::DrawTimer(float aftTime)
{
	int second = static_cast<int>(aftTime);
	int minute = second / 60;
	second %= 60;
	/*int hour = minute / 60;*/
	minute %= 60;

	int numberYfont = 3;
	std::string StringTime = std::to_string(minute);
	while (StringTime.length() != 2)
	{
		StringTime.insert(0, "0");
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	int Num = atoi(StringTime.substr(i, 1).c_str());
	//	//DrawGraph(1000 + 48 * i, 120,,true);
	//	DrawGraph((screenSize_.x / 2+fontHalfSizeX/2+ TimeOffset_) + ((ChipSize/2) *i), ResultfontOffsetY * 6- numberYfont - NumberAdapt_, lpImageMng.GetID("number.png")[Num], true);
	//}
	int colonOffset = 4;
	DrawGraph((screenSize_.x / 2 + fontHalfSizeX / 2 + TimeOffset_) + ((ChipSize / 2) * 1.5), ResultfontOffsetY * 6 - numberYfont - NumberAdapt_ + colonOffset, lpImageMng.GetID("colon.png")[0], true);
	for (int i = 0; i < 2; i++)
	{
		int Num = atoi(StringTime.substr(i, 1).c_str());
		DrawGraph((screenSize_.x / 2 + fontHalfSizeX / 2 + TimeOffset_) + ((ChipSize / 2 - colonOffset) * i), ResultfontOffsetY * 6 - numberYfont - NumberAdapt_, lpImageMng.GetID("number.png")[Num], true);

		//if (i < 2)
		//{
		//	//int Num = atoi(StringTime.substr(i, 1).c_str());
		//	DrawGraph((screenSize_.x / 2 + fontHalfSizeX / 2 + TimeOffset_) + ((ChipSize / 2- colonOffset) * i), ResultfontOffsetY * 6 - numberYfont - NumberAdapt_, lpImageMng.GetID("number.png")[Num], true);
		//}
		//else
		//{
		//	//int Num = atoi(StringTime.substr(i, 1).c_str());
		//	DrawGraph((screenSize_.x / 2 + fontHalfSizeX / 2 + TimeOffset_ + 7) + ((ChipSize / 2- colonOffset) * i), ResultfontOffsetY * 6 - numberYfont - NumberAdapt_, lpImageMng.GetID("number.png")[Num], true);
		//}

	}
	std::string StringTimeS = std::to_string(second);
	while (StringTimeS.length() != 2)
	{
		StringTimeS.insert(0, "0");
	}
	for (int i = 0; i < 2; i++)
	{
		int Num = atoi(StringTimeS.substr(i, 1).c_str());
		DrawGraph((screenSize_.x / 2 + fontHalfSizeX / 2 + TimeOffset_ + 7) + ((ChipSize / 2 - colonOffset) * (i+2)), ResultfontOffsetY * 6 - numberYfont - NumberAdapt_, lpImageMng.GetID("number.png")[Num], true);

	}
}

void ResultScene::DrawRestart(void)
{
	int restartfont = 6;
	int ReXoffset = 100;
	std::string StringTime = std::to_string(RECnt_);

	for (int i = 0; i < 2; i++)
	{
		int Num = atoi(StringTime.substr(i, 1).c_str());
		DrawGraph(screenSize_.x / 2 + ReXoffset - (ChipSize / 2) * i + RestartOffset_, ResultfontOffsetY * 4+ restartfont, lpImageMng.GetID("number.png")[Num], true);
	}

}
