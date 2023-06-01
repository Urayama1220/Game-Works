#include <DxLib.h>
#include "CrossOver.h"

CrossOver::CrossOver(uniqueScene beforScene, uniqueScene afterScene) : TransitionScene(beforScene, afterScene)
{
	limitTime_ = 25;
	/*limitTime_ = 3;*/
}

CrossOver::~CrossOver()
{
}

bool CrossOver::UpdateTransition()
{
	count += 0.2;
	DrawOwnScreen();
	if (count > limitTime_)
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto alpha = 255.0 * count / limitTime_;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast <int>(alpha));
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast <int>(alpha));
	afterScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

//void CrossOver::Draw(double delta)
//{
//	ClsDrawScreen();
//	auto alpha = 255.0 * count / limitTime_;
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast <int>(alpha));
//	beforScene_->Draw(delta);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast <int>(alpha));
//	afterScene_->Draw(delta);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
//}
