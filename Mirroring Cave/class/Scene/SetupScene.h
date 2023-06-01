#pragma once
#include "BaseScene.h"
#include "../Choice.h"
#include <string>
enum class NextSceneChoice
{
    Gamereturn,
    Restart,
    Select,
    Title,
    Tips,
    Max

};
class SetupScene :
	public BaseScene
{
public:
    static constexpr int slide_move_size = 56;
    static constexpr int point_offset = 120;
    SetupScene();
    SetupScene(Stage Choice, Stagelist& Slist, uniqueScene& ownScene /*,std::string Tips*/, int RECnt);
    ~SetupScene();
private:
    uniqueScene Update( uniqueScene ownScene)override;
    /*void Draw(double delta )override;*/
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::Setup;
    };
    //ゲームシーンの情報
    uniqueScene ownScene_;
    //ステージ格納
    Stage Choice_;
    //ヒント
    //表示フラグ
    bool Tipsflag_;
    //ヒント格納
    //std::string Tips_;
    //ゲームシーンでリスタートした回数
    int RECnt_;
    //現在のページ数
    int pageCnt_;
    //表示画像の座標
    Vector2 pos_;
    NextSceneChoice NextChoice_;
    int Cnt_;

    int ecSE;
    int ecS_;
    int ec_;
    int eccSE_;


    int StartTime_;
    int DrawAnimCnt_;
    bool fontDrawflag_;
    int DecisionCnt_;
};

