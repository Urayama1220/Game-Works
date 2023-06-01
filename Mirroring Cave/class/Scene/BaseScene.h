#pragma once
#include <memory>
#include "../common/Vector2.h"
#include "../Input/imput_Scene/Imput.h"
#include <list>
#include "../Choice.h"
using UniqueInput = std::shared_ptr<Imput>;
class BaseScene;
using uniqueScene = std::shared_ptr<BaseScene>;
using Stagelist = std::list<Stage>;
static constexpr int ChipSize = 48;
static constexpr int VolumeSE = 100;
enum class Scene
{
	Title,
	Game,
	Result,
	Select,
	Setup,
	HalfwayScene,
	Transition,
	GoResultScene,
	MAX
};

class BaseScene
{
public:
	BaseScene();
	virtual~BaseScene();
	virtual uniqueScene Update(uniqueScene ownScene) = 0;
	virtual void Draw();
	virtual bool Init(void) = 0 ;
	virtual void DrawOwnScreen() = 0;
	//下と下の下はやってることは同じ
	virtual Scene GetSceneID(void) = 0;//シーンの取得、設定
	double Offset_;	//オフセット
private:
protected:
	int screenID_;		//描画用
	Vector2 screenSize_;	//画面サイズ取得用変数
	
	UniqueInput imput_;
	Stagelist ClearStagelist_;
};

