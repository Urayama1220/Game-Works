#include <chrono>
#include <memory>
#include <DxLib.h>
#include "SceneMng.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "../Input/imput_Scene/keyboard.h"

//#include "../../_debug/_DebugConOut.h"
//#include "../../_debug/_DebugDispOut.h"

constexpr int ScreenSizeX = 1024;	//画面のXサイズ
constexpr int ScreenSizeY = 768;	//画面のYサイズ

void SceneMng::Run(void)
{
	if (!initFlag_)
	{
		if (!SysInit())		//もう一回調べてダメだったら返す
		{
			return;
		}
	}

	scene_ = std::make_unique<TitleScene>(imput_);
	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{
		/*_dbgStartDraw();*/

		scene_ = (scene_->Update(std::move(scene_)));
		Draw();
	}
}
void SceneMng::Update(void)
{
}
void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	scene_->Draw();
	/*_dbgDraw();*/
	ScreenFlip();
}
bool SceneMng::SysInit()
{
	SetWindowIconID(333);
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);			//最後の引数の60はVisuaでは回せるだけ回す
	ChangeWindowMode(true);				//
	if (DxLib_Init() == -1)				//Dxlibの初期化又
	{
		return false;
	}
	/*_dbgSetup(ScreenSizeX, ScreenSizeY, 255);*/
	SetWindowText("Mirroring Cave");
	imput_ = std::make_unique<keyboard>();
	return true;
}
SceneMng::SceneMng()
{
	initFlag_ = SysInit();
	
}

SceneMng::~SceneMng()
{
}
