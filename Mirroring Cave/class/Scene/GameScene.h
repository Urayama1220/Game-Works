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
    //�_�C�}�[���O���t�B�b�N�ŕ\��
    void DrawTimer(float aftTime);
    //���X�^�[�g���O���t�B�b�N�ŕ\��
    void DrawRestart(void);
    bool LoadMap(void);
    //���Ԋ֌W
    int StartTime;
    int EndTime;	//�I������
    int aftime;		//�o�ߎ���

   /* uniqueScene ownScene_;*/

    std::vector<char>objctVec_;
    rapidxml::xml_node<>* objctNode_;
    rapidxml::xml_document<> objctDoc;

    TmxObj tmxObj_;
    //�I�𒆂̃X�e�[�W�i�[
    Stage Choice_;
    //�q���g�摜�̊i�[�ꏊ
   /* std::string Tips_;*/
    
    //���X�^�[�g�񐔂̃J�E���g
    int RECnt_;
    //�Ƃ肠�����ʂɒǉ�����
    std::list<std::unique_ptr<Obj>> HintList_;
    Vector2Dbl pos_;
};

//template<class T> 
//inline void GameScene::createclass(T, int x, int y)
//{
//    objList_.emplace_back(std::make_unique<T>(x,y));
//}
