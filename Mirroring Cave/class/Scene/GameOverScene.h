#pragma once
#include "../common/Vector2.h"
#include "BaseScene.h"
#include "../../tmx/TmxObj.h"
#include "../Choice.h"
#include <list>
#include "../Obj/Obj.h"
class GameOverScene :
	public BaseScene
{
public:
    GameOverScene();
    GameOverScene(Stage Choice, Stagelist& Slist, int RECnt, UniqueInput& imput, uniqueScene beforScene);
    ~GameOverScene();
private:
    uniqueScene Update(uniqueScene ownScene)override;
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::GoResultScene;
    };
    //�Q�[���V�[���̏��
    uniqueScene ownScene_;
    /*uniqueScene afterScene_;*/
    //�X�e�[�W�i�[
    Stage Choice_;
    TmxObj tmxObj_;

    /*std::vector<char>objctVec_;
    rapidxml::xml_node<>* objctNode_;
    rapidxml::xml_document<> objctDoc;*/
    Vector2Dbl Playerpos_;
  /*  uniqueScene& beforScene_;*/

    bool startflag_;

    int animCnt_;
    int animOnCnt_;
    bool animflag_;

    int Spawn_moveCnt_;
    int AdjustmentSize_;
    int X_AdjustmentSize_;

    //���X�^�[�g�񐔂̃J�E���g
    int RECnt_;

    //std::list<std::unique_ptr<Obj>>objList_;
    int pageCnt_;
    int pageCnt_Max_;
    int UpMoveAnim_;


    int ecSE;
    int ecS_;
};

