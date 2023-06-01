#include "Crane.h"
#include "../../Common/ModelMng.h"
Crane::Crane()
{
    Init();
}

Crane::~Crane()
{
}

bool Crane::Init(void)
{
	pos_ = { -100,1800,650 };
    size_ = { 90,90,90 };
	MV1SetPosition(lpModelMng.GetID("./source/Model/Magnet/N_Box.mv1")[0], pos_.toVECTOR());
	Cranebody_ = lpStage.BulletCreateBox(0, pos_, size_.tobtVec(),0, size_.y, btScalar(0.3), btVector3(1, 1, 0), btVector3(1, 1, 1), Cranebody_);

	return false;
}

void Crane::Update(bool& MoveStartFlag)
{
    Vector3 vec ;
    btQuaternion qrot(0, 0, 0, 1);

    btTransform trans;
    if (MoveStartFlag)
    {
        if (Movetime_ <130)
        {
            vec = {0,-8,0};
        }
        if (Movetime_ > 130 && Movetime_ < 300)
        {
            vec = { 10,0,0 };
        }
        if (Movetime_ > 300)
        {
            vec = { 0,20,0 };
        }
        if (Movetime_ > 500)
        {
            Movetime_ = 0;
            MoveStartFlag = false;
            Cranebody_->getMotionState()->getWorldTransform(trans);
            trans.setOrigin({ -100,1800,650 });
            Cranebody_->getMotionState()->setWorldTransform(trans);
        }
        Movetime_++;
    }
   
    Cranebody_->getMotionState()->getWorldTransform(trans);
    trans.setOrigin(trans.getOrigin() + vec.tobtVec());
    Cranebody_->getMotionState()->setWorldTransform(trans);
    pos_ = Vector3(static_cast<float>(trans.getOrigin().x()), static_cast<float>(trans.getOrigin().y()), static_cast<float>(trans.getOrigin().z()));

    MV1SetPosition(lpModelMng.GetID("./source/Model/Magnet/N_Box.mv1")[0], pos_.toVECTOR());

    btMatrix3x3 rot = trans.getBasis();
    btVector3 euler;
    rot.getEulerZYX(euler[2], euler[1], euler[0]);

    MV1SetRotationXYZ(lpModelMng.GetID("./source/Model/Magnet/N_Box.mv1")[0], VGet(static_cast<float>(euler.x()), static_cast<float>(euler.y()), static_cast<float>(euler.z())));
}

void Crane::Draw(void)
{
    MV1DrawModel(lpModelMng.GetID("./source/Model/Magnet/N_Box.mv1")[0]);
}
