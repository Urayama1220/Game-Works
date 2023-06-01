#include "BulletManager.h"
#include"../../../Scene/SceneManager.h"
#include"../../CheckHit.h"
#include"../../../../_debug/_DebugDispOut.h"

constexpr float BULLET_CREATE_TIME = 2.0f;	//弾の生成時間
constexpr int BULLET_MAX_NUM = 16;			//弾の最大数

BulletManager::BulletManager()
{
	Init();
}

BulletManager::~BulletManager()
{
}

void BulletManager::Init(void)
{
	bulletFiringTime_ = 0.0f;
	bulletNum_ = 0;
	bullets_.reserve(BULLET_MAX_NUM);
}

void BulletManager::Create(Vector3 playerpos, Vector3 enemypos)
{
	//弾の発射方向取得
	auto direction = (playerpos - enemypos).Normalized();

	//一定時間で弾を生成
	if (bulletFiringTime_ >= BULLET_CREATE_TIME)
	{
		bulletFiringTime_ = 0.0;

		//要素のうち、生存していないものは使いまわす
		for (auto& bullet : bullets_)
		{
			if (!bullet->GetisAlive())
			{
				bullet->Init(direction, enemypos);
				bullet->SetisAlive(true);
				break;
			}
		}
		//全て生存している場合は追加する
		//上限を超えている場合は追加しない
		if (bulletNum_ < BULLET_MAX_NUM)
		{
			bullets_.emplace_back(std::make_unique<Bullet>(direction, enemypos, bulletNum_));
			bulletNum_++;
		}
	}
	bulletFiringTime_ += lpSceneMng.GetDeltaTime();
}

void BulletManager::Release(void)
{
	bullets_.clear();
	bullets_.shrink_to_fit();
}

void BulletManager::Move(void)
{
	for (auto& bullet : bullets_)
	{
		if (bullet->GetisAlive())
		{
			//弾の更新
			bullet->Update();

			//弾の破棄チェック
			if (bullet->CheckAlive())
			{
				//生存時間を過ぎていた場合破棄する
				bullet->SetisAlive(false);
			}
		}
	}
}

void BulletManager::Draw()
{
	//弾の描画
	for (auto& bullet : bullets_)
	{
		if (bullet->GetisAlive())
		{
			bullet->Draw();
		}
	}
}

//判定する必要あり
void BulletManager::CollisionRodAndBullet(Line line, Line right, Line left)
{
	for (auto& bullet : bullets_)
	{
		int num = bullet->GetNumber();
		if (CollisionRay()(line, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag ||
			CollisionRay()(right, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag ||
			CollisionRay()(left, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag)
		{
			//当たっているならスピードダウンしていって最終的にベクトルが反転する
			bullet->DownSpeed();
		}
	}
}

std::vector<std::shared_ptr<Bullet>>& BulletManager::GetBulletVector(void)
{
	return bullets_;
}
