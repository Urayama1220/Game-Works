#include <DxLib.h>
#include "../common/imageMng.h"

#include "Half.h"
Half::Half()
{
    Init();
}
Half::Half(double x, double y, bool die)
{
    Init(x,y, die);
}
Half::~Half()
{
}

bool Half::Init()
{
    Obtype_ = objType::Half;
    pos_ = { 0,0 };
    size_ = { square_size,square_size };
    moveStop_checkdie_flag = false;
    lpImageMng.GetID("image/Obj/Half1.png", "Half");
	return false;
}



bool Half::Init(double x, double y, bool die)
{
    Init();
    pos_ = { x * square_size,y * square_size };
    moveStop_checkdie_flag = die;

    return false;
}

void Half::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
}

void Half::Draw(void)
{
    /*DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xff00ff, false);*/
    /*DrawBox(static_cast<int>(pos_.x),
        static_cast<int>(pos_.y),
        static_cast<int>(pos_.x) + static_cast<int>(size_.x),
        static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
    DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("Half")[0], true);
}

