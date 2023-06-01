#include <DxLib.h>
#include "FadeinOut.h"

FadeinOut::FadeinOut( uniqueScene beforScene, uniqueScene afterScene) : TransitionScene(beforScene, afterScene)
{
	limitTime_ = 20;
	/*limitTime_ = 3;*/
}

FadeinOut::~FadeinOut()
{
}

bool FadeinOut::UpdateTransition()
{
	count += 0.2;
	
	if (count > limitTime_)
	{
		return true;
	}
	return false;
}

void FadeinOut::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto alpha = static_cast <int>(255.0 * count / (limitTime_ / 2));

	if (alpha < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
		beforScene_->Draw();
	}
	else
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha - 255);
		afterScene_->Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

//void FadeinOut::Draw(double delta)
//{
//	ClsDrawScreen();
//	auto alpha = static_cast < int>(255.0 * count / (limitTime_/2));
//	
//	if (alpha < 255)
//	{
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
//		beforScene_->Draw(delta);
//	}
//	else
//	{
//		
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha-255 );
//		afterScene_->Draw(delta);
//	}
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
//}
