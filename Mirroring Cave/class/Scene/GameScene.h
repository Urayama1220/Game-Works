#pragma once
#include <memory>
#include <list>
#include <string>
#include "BaseScene.h"
#include "../../tmx/TmxObj.h"
#include "../Obj/Obj.h"
#include "../Choice.h"
class Obj;
class GameScene :
    public BaseScene
{
public:
    GameScene();
    GameScene(Stage Choice , Stagelist& Slist);
    GameScene(Stage Choice, Stagelist& Slist, UniqueInput& imput);
    GameScene(Stage Choice , Stagelist& Slist, int RECnt, UniqueInput& imput);
    ~GameScene();
    std::list<std::unique_ptr<Obj>>objList_;
private:
    uniqueScene Update(uniqueScene ownScene)override;
    /*void Draw(double delta )override;*/
    void DrawOwnScreen(void)override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::Game;
    };
  /*  template <class T>
    void createclass(T,int x,int y);*/

    bool Timer(void);
    //ダイマーをグラフィックで表示
    void DrawTimer(float aftTime);
    //リスタートをグラフィックで表示
    void DrawRestart(void);
    bool LoadMap(void);
    //時間関係
    int StartTime;
    int EndTime;	//終了時間
    int aftime;		//経過時間

   /* uniqueScene ownScene_;*/

    std::vector<char>objctVec_;
    rapidxml::xml_node<>* objctNode_;
    rapidxml::xml_document<> objctDoc;

    TmxObj tmxObj_;
    //選択中のステージ格納
    Stage Choice_;
    //ヒント画像の格納場所
   /* std::string Tips_;*/
    
    //リスタート回数のカウント
    int RECnt_;
    //とりあえず個別に追加する
    std::list<std::unique_ptr<Obj>> HintList_;
    Vector2Dbl pos_;
};

//template<class T> 
//inline void GameScene::createclass(T, int x, int y)
//{
//    objList_.emplace_back(std::make_unique<T>(x,y));
//}
