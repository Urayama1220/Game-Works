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
    //�Q�[���V�[���̏��
    uniqueScene ownScene_;
    //�X�e�[�W�i�[
    Stage Choice_;
    //�q���g
    //�\���t���O
    bool Tipsflag_;
    //�q���g�i�[
    //std::string Tips_;
    //�Q�[���V�[���Ń��X�^�[�g������
    int RECnt_;
    //���݂̃y�[�W��
    int pageCnt_;
    //�\���摜�̍��W
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

