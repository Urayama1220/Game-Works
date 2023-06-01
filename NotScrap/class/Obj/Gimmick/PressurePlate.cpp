#include "PressureDoor.h"
#include "PressureSidewaysDoor.h"
#include "PressurePlate.h"
#include "../Stage.h"
//コンストラクタ
PressurePlate::PressurePlate(Vector3 pPos, Vector3 dPos, DoorType type,int num)
{
	num_ = num;
	Init(pPos,dPos,type);
}

//デストラクタ
PressurePlate::~PressurePlate()
{
}

//初期化
bool PressurePlate::Init()
{
	return true;
}

bool PressurePlate::Init(Vector3 pPos, Vector3 dPos,DoorType type)
{
	//担当.三ヶ島滉季(開始)---------------------------------------------------------------------------
	//ボタン座標
	pos_ = pPos;
	//扉座標
	doorPos_ = dPos;
	//種類
	type_ = type;
	if (type == DoorType::SidewaysDoor)
	{
		//横移動扉
		Sdoor_ = std::make_unique<PressureSidewaysDoor>(doorPos_, num_);
	}
	else
	{
		//縦移動扉
		door_ = std::make_unique<PressureDoor>(doorPos_, num_);
	}

	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_], pos_.toVECTOR());
	MV1SetPosition(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_], pos_.toVECTOR());
	MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_], VECTOR{ 1.8f,1.8f,1.8f });
	MV1SetScale(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_], VECTOR{ 1.8f,1.8f,1.8f });
	MV1RefreshCollInfo(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_]);
	//担当.三ヶ島滉季(終了)---------------------------------------------------------------------------
	return true;
}

//更新
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


//描画
void PressurePlate::Draw(void)
{
	//担当.三ヶ島滉季(開始)---------------------------------------------------------------------------
	if (flg_)
	{
		MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/OnButton.mv1")[num_]);
	}	
	else 
	{
		MV1DrawModel(lpModelMng.GetID("./source/Model/Gimmick/Button.mv1")[num_]);
	}
	//担当.三ヶ島滉季(終了)---------------------------------------------------------------------------
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
				//TRACE("敵に当たった\n");
				hitFlag = true;
			}
			//衝突判定用の動的構造体のメモリー解放
			MV1CollResultPolyDimTerminate(hits);
		}
	}
	return hitFlag;
}

