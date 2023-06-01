#include <DxLib.h>
#include "../common/imageMng.h"

#include "OneWay.h"
OneWay::OneWay()
{
    Init();
}
OneWay::OneWay(double x, double y, bool die, MOVE_DIRECTION dir)
{
    Moveabledir = dir;  //‰¼
    Init(x,y, die);
}
OneWay::~OneWay()
{
}

bool OneWay::Init()
{
    Obtype_ = objType::Half;
    pos_ = { 0,0 };
    size_ = { square_size,square_size };
    moveStop_checkdie_flag = false;
   
    lpImageMng.GetID("image/Obj/oneway.png", "oneway", { 48,48 }, {4,1});
	return false;
}



bool OneWay::Init(double x, double y, bool die)
{
    Init();
    pos_ = { x * square_size,y * square_size };
    moveStop_checkdie_flag = die;

    return false;
}

void OneWay::Updata(TmxObj& tmxObj_, ObjUlist& objList_)
{
}

void OneWay::Draw(void)
{
    /*DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xff00ff, false);*/
    /*DrawBox(static_cast<int>(pos_.x),
        static_cast<int>(pos_.y),
        static_cast<int>(pos_.x) + static_cast<int>(size_.x),
        static_cast<int>(pos_.y) + static_cast<int>(size_.y), 0xff00ff, false);*/
    TRACE("%d\n", static_cast<int>(Moveabledir));
    DrawGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), lpImageMng.GetID("oneway")[static_cast<int>(Moveabledir)], true);
}

