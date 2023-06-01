#pragma once
#include "../BaseScene.h"
enum class Transition
{
    //トランジションの種類
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
    virtual bool UpdateTransition() = 0;    //エフェクトアップデート
protected:
    uniqueScene beforScene_;    //前のシーン
    uniqueScene afterScene_;    //次のシーン

    double count;
    /*float limit time;*/
};

