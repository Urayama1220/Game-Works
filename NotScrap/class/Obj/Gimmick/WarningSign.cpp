#include "WarningSign.h"

WarningSign::WarningSign(Vector3& pos, int num)
{
	num_ = num;
	Init(pos);
}

WarningSign::~WarningSign(void)
{
}

bool WarningSign::Init(void)
{
	return true;
}

bool WarningSign::Init(Vector3& pos)
{
	//���W
	pos_ = pos;
	//�z�u
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/sign.mv1")[num_], { pos_.x,pos.y,pos.z });
	return true;
}

void WarningSign::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{
}

void WarningSign::Update(bool& flg)
{
}

void WarningSign::Draw(void)
{
	MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/sign.mv1")[num_]);
}

btRigidBody* WarningSign::GetRigidBody(void)
{
	return nullptr;
}
