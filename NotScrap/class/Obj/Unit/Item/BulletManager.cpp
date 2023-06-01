#include "BulletManager.h"
#include"../../../Scene/SceneManager.h"
#include"../../CheckHit.h"
#include"../../../../_debug/_DebugDispOut.h"

constexpr float BULLET_CREATE_TIME = 2.0f;	//�e�̐�������
constexpr int BULLET_MAX_NUM = 16;			//�e�̍ő吔

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
	//�e�̔��˕����擾
	auto direction = (playerpos - enemypos).Normalized();

	//��莞�ԂŒe�𐶐�
	if (bulletFiringTime_ >= BULLET_CREATE_TIME)
	{
		bulletFiringTime_ = 0.0;

		//�v�f�̂����A�������Ă��Ȃ����͎̂g���܂킷
		for (auto& bullet : bullets_)
		{
			if (!bullet->GetisAlive())
			{
				bullet->Init(direction, enemypos);
				bullet->SetisAlive(true);
				break;
			}
		}
		//�S�Đ������Ă���ꍇ�͒ǉ�����
		//����𒴂��Ă���ꍇ�͒ǉ����Ȃ�
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
			//�e�̍X�V
			bullet->Update();

			//�e�̔j���`�F�b�N
			if (bullet->CheckAlive())
			{
				//�������Ԃ��߂��Ă����ꍇ�j������
				bullet->SetisAlive(false);
			}
		}
	}
}

void BulletManager::Draw()
{
	//�e�̕`��
	for (auto& bullet : bullets_)
	{
		if (bullet->GetisAlive())
		{
			bullet->Draw();
		}
	}
}

//���肷��K�v����
void BulletManager::CollisionRodAndBullet(Line line, Line right, Line left)
{
	for (auto& bullet : bullets_)
	{
		int num = bullet->GetNumber();
		if (CollisionRay()(line, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag ||
			CollisionRay()(right, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag ||
			CollisionRay()(left, lpModelMng.GetID("./source/Model/Enemy/bullet.mv1")[num]).HitFlag)
		{
			//�������Ă���Ȃ�X�s�[�h�_�E�����Ă����čŏI�I�Ƀx�N�g�������]����
			bullet->DownSpeed();
		}
	}
}

std::vector<std::shared_ptr<Bullet>>& BulletManager::GetBulletVector(void)
{
	return bullets_;
}
