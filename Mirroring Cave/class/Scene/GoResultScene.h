#pragma once
#include "../common/Vector2.h"
#include "BaseScene.h"
#include "../../tmx/TmxObj.h"
#include "../Choice.h"
#include <list>
#include "../Obj/Obj.h"
using Poslist = std::list<Vector2Dbl>;
static constexpr double square_goresult_size = 48.0;
static constexpr int animCntmax = 26;
static constexpr int Spawn_moveMaxCnt_ = 20;
class GoResultScene :
	public BaseScene
{
public:
    GoResultScene();
    GoResultScene(Stage Choice, Stagelist& Slist, int time, int RECnt, UniqueInput& imput,Vector2Dbl Pos);
    ~GoResultScene();
private:
    uniqueScene Update(uniqueScene ownScene)override;
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::GoResultScene;
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

    Vector2Dbl GoalPos_;
    Vector2Dbl GoalEfPos_;
    int GoalanimeCnt_;	//ゴールのアニメーションカウント
   /* std::list<std::unique_ptr<Obj>>objList_;*/

    bool startflag_;

    int animCnt_;
    bool animflag_;

    int Spawn_moveCnt_;
    int AdjustmentSize_;
    int X_AdjustmentSize_;

    //リスタート回数のカウント
    int RECnt_;

    int aftime;		//経過時間

    //std::list<std::unique_ptr<Obj>>objList_;

    int UpMoveAnim_;


    int SE_;
};

