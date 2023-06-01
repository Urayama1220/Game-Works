#include <DxLib.h>
#include "TransitionScene.h"
#include "../../../_debug/_DebugConOut.h"
TransitionScene::TransitionScene(uniqueScene& beforScene, uniqueScene& afterScene)
{
	beforScene_ = std::move( beforScene);
	afterScene_ = std::move(afterScene);
	TRACE("TransitionSceneÇÃê∂ê¨\n");
	Init();
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init()
{
	count = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw();
	return false;
}

uniqueScene TransitionScene::Update( uniqueScene ownScene)
{
	//count += delta;
	//
	if (/*count > 3*/UpdateTransition())
	{
		TRACE("éüÇÃÉVÅ[ÉìÇ…à⁄çs\n");
		return std::move( afterScene_);
	}
	DrawOwnScreen();
	return ownScene;
}

//void TransitionScene::Draw(double delta)
//{
//	ClsDrawScreen();
//	auto alpha = 255.0 * count / 3.0;
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast <int>(alpha));
//	beforScene_->Draw(delta);
//	
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast <int>(alpha));
//	afterScene_->Draw(delta);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
//}
