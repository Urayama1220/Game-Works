#pragma once
#include "TransitionScene.h"
class FadeinOut :
    public TransitionScene
{
public:
    FadeinOut(uniqueScene beforScene, uniqueScene afterScene);
    ~FadeinOut();

private:
    double limitTime_;

    bool UpdateTransition()override;
    /*void Draw(double delta);*/
    void DrawOwnScreen()override;

};

