#pragma once
#include "BaseScene.h"
#include <list>
#include "../Obj/Obj.h"
#include "../../tmx/TmxObj.h"
class Obj;
class TitleScene :
	public BaseScene
{
   
public:
    static constexpr double Installation_offset = 48;
    TitleScene(UniqueInput& imput);
    ~TitleScene();
    std::list<std::unique_ptr<Obj>>objTitleList_;
private:
    uniqueScene Update(uniqueScene ownScene)override;
    void DrawOwnScreen()override;
    bool Init(void)override;
    Scene GetSceneID(void)override {
        return Scene::Title;
    };
    int Timecnt_;
    int Timecnt_SE_Max_;
    int Timecnt_Max_;
    TmxObj tmxObj_;
    int objTitlestartCnt_;
    int objTitleCnt_;
    int objTitlestartCnt_Max_;
    int objTitleCnt_Max_;
    int starttitle_;
    int ecSE_;

    Vector2 LogoSplitSize_;
   // Vector2 LogoLastSize_;
    int titleflameCnt_;
    bool title1;
    bool title2;
    bool title3;
    bool title4;

    int titleInmove_;

};

