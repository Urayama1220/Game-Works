#include "PressureDoor.h"
//�R���X�g���N�^
PressureDoor::PressureDoor(Vector3& pos,int num)
{
	num_ = num;
	Init(pos);
}

//�f�X�g���N�^
PressureDoor::~PressureDoor()
{
}


bool PressureDoor::Init(void)
{
	return false;
}

bool PressureDoor::Init(Vector3& pos)
{
	//�S��.�O������G(�J�n)---------------------------------------------------------------------------
	//���W
	pos_ = pos;
	//�ړ���
	movePow_ = 5;
	//�傫��
	size_ = {10,190,180};
	//�J�t���O
	flg_ = false;
	//�ړ�����l
	moveLimitVal_ = { pos_.y + DOOR_SIZE_Y, pos_.y };
	//�z�u
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_], pos_.toVECTOR()/*{ pos_.x, pos_.y, pos_.z }*/);
	//�S��.�O������G(�I��)---------------------------------------------------------------------------
	Doorbody_ = lpStage.BulletCreateBox(1,pos_,size_.tobtVec(),0 ,size_.y, btScalar(0.3), btVector3(0, 1, 0), btVector3(0, 0, 0), Doorbody_);
	return true;
}

//�X�V
void PressureDoor::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{
}

void PressureDoor::Update(bool& flg)
{
	flg_ = flg;
	btTransform trans;
	Doorbody_->getMotionState()->getWorldTransform(trans);

	pos_ = Vector3(static_cast<float>(trans.getOrigin().x()), static_cast<float>(trans.getOrigin().y()), static_cast<float>(trans.getOrigin().z()));

	//�X�C�b�`�����܂ꂽ��
	if (flg_)
	{
		//����܂Ŕ����㏸
		auto vec = moveLimitVal_.upper  - pos_.y;
		Doorbody_->setLinearVelocity({ 0,vec,0});

	}
	//���W�X�V
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_], pos_.toVECTOR()/*{ pos_.x, pos_.y, pos_.z }*/);
}


//�`��
void PressureDoor::Draw(void)
{
	MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_]);
}

btRigidBody* PressureDoor::GetRigidBody(void)
{
	return nullptr;
}

//�v���C���[���{�^���𓥂�ł��邩
void PressureDoor::SetStepOnFlg(bool flg)
{
	flg_ = flg;
}
