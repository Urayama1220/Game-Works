#include "Accessory.h"
#include "../Stage.h"
#include"../../../_debug/_DebugConOut.h"

Accessory::Accessory(Vector3 pos, int num)
{
    num_ = num;
    Init( pos, num);
}

Accessory::~Accessory()
{
}

bool Accessory::Init(Vector3 pos, int num)
{
    //íSìñ.éOÉñìáü‰ãG(äJén)---------------------------------------------------------------------------

    //ç¿ïW
    pos_ = pos;
    //ägëÂíl
    size_ = { 50,50,30 };
    MV1SetPosition(lpModelMng.GetID("./source/Model/Stage/Barrel2.mv1")[num_], pos_.toVECTOR());
    //íSìñ.éOÉñìáü‰ãG(èIóπ)---------------------------------------------------------------------------

    Acsbody_ = lpStage.BulletCreateSphere(pos_, btScalar(size_.y), btScalar(0.3), btVector3(1, 1, 1), btVector3(1, 1, 1), Acsbody_);

    return true;
}

void Accessory::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{
    //íSìñ.éOÉñìáü‰ãG(äJén)---------------------------------------------------------------------------
    //çXêVèàóù
    MV1SetPosition(lpModelMng.GetID("./source/Model/Stage/Barrel2.mv1")[num_], pos_.toVECTOR());
    //íSìñ.éOÉñìáü‰ãG(èIóπ)---------------------------------------------------------------------------

    btQuaternion qrot(0, 0, 0, 1);

    btTransform trans;
    Acsbody_->getMotionState()->getWorldTransform(trans);
    pos_ = Vector3(static_cast<float>(trans.getOrigin().x()), static_cast<float>(trans.getOrigin().y()), static_cast<float>(trans.getOrigin().z()));

    btMatrix3x3 rot = trans.getBasis();
    btVector3 euler;
    rot.getEulerZYX(euler[2], euler[1], euler[0]);
    MV1SetRotationXYZ(lpModelMng.GetID("./source/Model/Stage/Barrel2.mv1")[num_], VGet(static_cast<float>(euler.x()), static_cast<float>(euler.y()), static_cast<float>(euler.z())));
    MV1RefreshCollInfo(lpModelMng.GetID("./source/Model/Stage/Barrel2.mv1")[num_]);

}

void Accessory::Draw(void)
{

	MV1DrawModel(lpModelMng.GetID("./source/Model/Stage/Barrel2.mv1")[num_]);
}


btRigidBody* Accessory::GetRigidBody(void)
{
    return Acsbody_;
}

Vector3 Accessory::GetPos()
{
    return pos_;
}

void Accessory::SetMoveVec(Vector3 vec)
{
    moveVec_ = vec;
}
