#include "PressureDoor.h"
//コンストラクタ
PressureDoor::PressureDoor(Vector3& pos,int num)
{
	num_ = num;
	Init(pos);
}

//デストラクタ
PressureDoor::~PressureDoor()
{
}


bool PressureDoor::Init(void)
{
	return false;
}

bool PressureDoor::Init(Vector3& pos)
{
	//担当.三ヶ島滉季(開始)---------------------------------------------------------------------------
	//座標
	pos_ = pos;
	//移動量
	movePow_ = 5;
	//大きさ
	size_ = {10,190,180};
	//開閉フラグ
	flg_ = false;
	//移動上限値
	moveLimitVal_ = { pos_.y + DOOR_SIZE_Y, pos_.y };
	//配置
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_], pos_.toVECTOR()/*{ pos_.x, pos_.y, pos_.z }*/);
	//担当.三ヶ島滉季(終了)---------------------------------------------------------------------------
	Doorbody_ = lpStage.BulletCreateBox(1,pos_,size_.tobtVec(),0 ,size_.y, btScalar(0.3), btVector3(0, 1, 0), btVector3(0, 0, 0), Doorbody_);
	return true;
}

//更新
void PressureDoor::Update(std::vector<std::shared_ptr<Player>>& PlyaerList, GimmickList& gimmickList)
{
}

void PressureDoor::Update(bool& flg)
{
	flg_ = flg;
	btTransform trans;
	Doorbody_->getMotionState()->getWorldTransform(trans);

	pos_ = Vector3(static_cast<float>(trans.getOrigin().x()), static_cast<float>(trans.getOrigin().y()), static_cast<float>(trans.getOrigin().z()));

	//スイッチが踏まれたら
	if (flg_)
	{
		//上限まで扉を上昇
		auto vec = moveLimitVal_.upper  - pos_.y;
		Doorbody_->setLinearVelocity({ 0,vec,0});

	}
	//座標更新
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_], pos_.toVECTOR()/*{ pos_.x, pos_.y, pos_.z }*/);
}


//描画
void PressureDoor::Draw(void)
{
	MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/Door.mv1")[num_]);
}

btRigidBody* PressureDoor::GetRigidBody(void)
{
	return nullptr;
}

//プレイヤーがボタンを踏んでいるか
void PressureDoor::SetStepOnFlg(bool flg)
{
	flg_ = flg;
}
