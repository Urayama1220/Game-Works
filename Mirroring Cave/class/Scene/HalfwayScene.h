#pragma once
#include "../common/Vector2.h"
#include "BaseScene.h"
#include "../../tmx/TmxObj.h"
#include "../Choice.h"
#include <list>
using Poslist = std::list<Vector2Dbl>;
//static constexpr double square_size = 48.0;
static constexpr int animCntmax = 9;
static constexpr int animSize = 10;
class HalfwayScene :
	public BaseScene
{
public:
    HalfwayScene();
    HalfwayScene(Stage Choice, Stagelist& Slist, UniqueInput& imput);
    HalfwayScene(Stage Choice, Stagelist& Slist, int RECnt, UniqueInput& imput);
    ~HalfwayScene();
private:
    uniqueScene Update(uniqueScene ownScene)override;
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::HalfwayScene;
    };
    //ゲームシーンの情報
  /*  uniqueScene ownScene_;*/
    /*uniqueScene afterScene_;*/
    //ステージ格納
    Stage Choice_;
    TmxObj tmxObj_;

    std::vector<char>objctVec_;
    rapidxml::xml_node<>* objctNode_;
    rapidxml::xml_document<> objctDoc;
    Poslist Poslist_;
    Vector2Dbl Playerpos_;

    bool startflag_;

    int animCnt_;
    bool animflag_;
    int Spawn_moveCnt;
    int Spawn_moveMaxCnt_;
    int StartAnimOffset_X_;
    int StartAnimOffset_Y_;
    int StartSize_;
    int Objoffset_;
    //リスタート回数のカウント
    int RECnt_;
};

