#include <DxLib.h>
#include "BaseScene.h"

BaseScene::BaseScene() 
{
	//screenID‚ÌƒXƒNƒŠ[ƒ“‚ğì¬
	SetDrawScreen(DX_SCREEN_BACK);
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y,true);
	Offset_ = 1;
	//---
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{
	DrawGraph(0, 0, screenID_, true);
}
