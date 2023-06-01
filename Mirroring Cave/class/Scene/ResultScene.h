#pragma once
#include "BaseScene.h"
#include "../Choice.h"
static constexpr int fontHalfSizeX = 58;
static constexpr int ResultfontOffsetY = 88;
static constexpr int BLEND_NOBLEND = 100;

class ResultScene :
	public BaseScene
{
public:
    ResultScene();
    ResultScene(Stage Choice, Stagelist& Slist, int time, int RECnt, UniqueInput& imput);
    ~ResultScene();
private:
    uniqueScene Update( uniqueScene ownScene)override;
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::Result;
    };
  
    //�X�e�[�W�i�[
    Stage Choice_;
    //�Q�[���V�[���Ń��X�^�[�g������
    int RECnt_;
    //�Q�[���V�[���̌o�ߎ���
    int GemeTime_;

    void DrawTimer(float aftTime);
    void DrawRestart(void);

    int TimeOffset_;
    int RestartOffset_;
    int AdaptSize_;
    int NumberAdapt_;
    int Timecnt_;

    int gemaclearCnt_;
    int gemaclearCnt_move_;
    Vector2 curtainCnt_;
    bool DrawResultflag_;
    int DrawResultCnt_;

    int eSE_;
    int eccSE_;

    Stagelist OldClearStagelist_;
};

