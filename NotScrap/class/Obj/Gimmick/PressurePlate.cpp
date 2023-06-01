#include "PressureDoor.h"
#include "PressureSidewaysDoor.h"
#include "PressurePlate.h"
#include "../Stage.h"
//�R���X�g���N�^
PressurePlate::PressurePlate(Vector3 pPos, Vector3 dPos, DoorType type,int num)
{
	num_ = num;
	Init(pPos,dPos,type);
}

//�f�X�g���N�^
PressurePlate::~PressurePlate()
{
}

//������
bool PressurePlate::Init()
{
	return true;
}

bool PressurePlate::Init(Vector3 pPos, Vector3 dPos,DoorType type)
{
	//�S��.�O������G(�J�n)---------------------------------------------------------------------------
	//�{�^�����W
	pos_ = pPos;
	//�����W
	doorPos_ = dPos;
	//���
	type_ = type;
	if (type == DoorType::SidewaysDoor)
	{
		//���ړ���
		Sdoor_ = std::make_unique<PressureSidewaysDoor>(doorPos_, num_);
	}
	else
	{
		//�c�ړ���
		door_ = std::make_unique<PressureDoor>(doorPos_, num_);
	}

	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_], pos_.toVECTOR());
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_], pos_.toVECTOR());
	MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_], VECTOR{ 1.8f,1.8f,1.8f });
	MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_], VECTOR{ 1.8f,1.8f,1.8f });
	MV1RefreshCollInfo(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_]);
	//�S��.�O������G(�I��)---------------------------------------------------------------------------
	return true;
}

//�X�V
void PressurePlate::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{
	flg_ = HitMagBox(flg_,gimmickList);
	if (type_ == DoorType::SidewaysDoor)
	{
		Sdoor_->Update(flg_);
	}
	else
	{
		door_->Update(flg_);
	}	
}


//�`��
void PressurePlate::Draw(void)
{
	//�S��.�O������G(�J�n)---------------------------------------------------------------------------
	if (flg_)
	{
		MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_]);
	}	
	else 
	{
		MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_]);
	}
	//�S��.�O������G(�I��)---------------------------------------------------------------------------
	if (type_ == DoorType::SidewaysDoor)
	{
		Sdoor_->Draw();
	}
	else
	{
		door_->Draw();
	}
}

btRigidBody* PressurePlate::GetRigidBody(void)
{
	return nullptr;
}

bool PressurePlate::HitMagBox(bool flag,GimmickList& gimmickList)
{
	bool hitFlag = false;
	for (auto& box : gimmickList)
	{
		if (box->GetObjType() == objType::NMagBox || box->GetObjType() == objType::SMagBox)
		{
			auto hits = MV1CollCheck_Sphere(
				lpModelMng.GetID("./source/Model/Magnet/N_Box.mv1")[box->GetModelH()],
				-1,
				pos_.toVECTOR(), 50);

			if (hits.HitNum > 0)
			{
				//TRACE("�G�ɓ�������\n");
				hitFlag = true;
			}
			//�Փ˔���p�̓��I�\���̂̃������[���
			MV1CollResultPolyDimTerminate(hits);
		}
	}
	return hitFlag;
}

