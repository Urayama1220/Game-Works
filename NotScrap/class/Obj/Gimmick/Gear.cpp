#include "Gear.h"
#include "../Stage.h"

Gear::Gear(Vector3 pos,int num, string modelName)
{
	num_ = num;
	Init(pos, modelName);
}

Gear::~Gear()
{
}

bool Gear::Init(Vector3 pos, string modelName)
{
    //íSìñ.éOÉñìáü‰ãG(äJén)---------------------------------------------------------------------------
	pos_ = pos;
    SetGearModel(modelName);
    //íSìñ.éOÉñìáü‰ãG(èIóπ)---------------------------------------------------------------------------
	return true;
}

void Gear::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{

    MV1SetRotationXYZ(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], VGet(0, 0,time_));
    MV1RefreshCollInfo(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_]);
    time_++;
}

void Gear::Draw(void)
{
	MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_]);
}


void Gear::SetGearModel(string modelName)
{
    if (modelName == "Gear_S")
    {
        MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], { 0.25,0.25,1.0 });
        MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], pos_.toVECTOR());
    }
    if (modelName == "Gear_M")
    {
        MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], { 0.5,0.5,1.0 });
        MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], pos_.toVECTOR());
    }
    if (modelName == "Gear_L")
    {
        MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], { 1.0,1.0,1.0 });
	    MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Gear.mv1")[num_], pos_.toVECTOR());
    }

}
