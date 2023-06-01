#pragma once
#include "TransitionScene.h"
class CrossOver :
    public TransitionScene
{
public:
    CrossOver(uniqueScene beforScene, uniqueScene afterScene);
    ~CrossOver();

private:
    double limitTime_;
    
    bool UpdateTransition()override;
   /* void Draw(double delta);*/
    void DrawOwnScreen()override;

};

