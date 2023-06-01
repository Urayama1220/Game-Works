#pragma once
#include "BaseScene.h"
#include "../Choice.h"
#include "../common/Vector2.h"
#include "../Input/Controller.h"
using uniCon = std::unique_ptr< Controller>;
static constexpr int ExpSize  = 70;

class SelectScene :
	public BaseScene
{
public:
    static constexpr int  selectionmove = 8;
    SelectScene(UniqueInput& imput);
    SelectScene(Stage Choice, Stagelist& Slist, UniqueInput& imput);
    SelectScene(Stage Choice, Stagelist& Slist, Stagelist& OldSlist, UniqueInput& imput);
    ~SelectScene();
private:
    uniqueScene Update(uniqueScene ownScene)override;
    /*void Draw(double delta )override;*/
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::Select;
    };
    Stage Choice_;
    Vector2 pos_;
    uniCon controller_;
    int pageCnt_;
    //@
    int pageCnt_Ten_;

    int alphaCnt_;
    //‘I‘ð‚µ‚½‚Æ‚«‚Ì‘S‘Ì‚ðˆÚ“®‚³‚¹‚é
    int selectionPos_;
    bool selectionMoveflag_;
    bool selectionFix_;
    Vector2 CenterMovestorage_;

    bool skipflag_;

    int alphaOnCnt_;
    int MapUpBlendCnt_;
    int ecSE;
    int ecS_;
    int ec_;
    int e_;

    int MaxpegeCnt_;
    int selectnowmove_;
    int smallsize_[20];


    int MoveCnt_;
    int animbuttonCnt_;

    int ClearfadeinStartCnt_;
    bool ClearfadeinGoflag_;
    int ClearfadeinCnt_;
    bool OldClearStage_;
    int inbatchCnt_;

    Stagelist OldClearStagelist_;
};

