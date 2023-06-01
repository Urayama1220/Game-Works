#pragma once
#include "../BaseScene.h"
enum class Transition
{
    //�g�����W�V�����̎��
    CrossFade,
    FadeInOut,
    MAX
};
class TransitionScene : 
    public BaseScene
{
public:
    TransitionScene(uniqueScene& beforScene, uniqueScene& afterScene);
    ~TransitionScene();

    Scene GetSceneID(void)override final{
        return Scene::Transition;
    };

private:
    bool Init();
    uniqueScene Update(uniqueScene ownScene)override;
   /* void Draw(double delta);*/
    virtual bool UpdateTransition() = 0;    //�G�t�F�N�g�A�b�v�f�[�g
protected:
    uniqueScene beforScene_;    //�O�̃V�[��
    uniqueScene afterScene_;    //���̃V�[��

    double count;
    /*float limit time;*/
};

