#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"../../Common/ImageMng.h"
#include "EnemyShoot.h"
#include"Item/BulletManager.h"
#include"../../Scene/SceneManager.h"
#include"../../../_debug/_DebugDispOut.h"
#include "../../Common/SoundMng.h"
#include "../Unit/Player.h"

constexpr float MOVE_SPEED = 50.0f;	//�������x
constexpr float ROT_TIME = 1.5f;	//��]��������܂ł̎���
constexpr float SPHERE_SIZE = 50.0f;	//�����蔻��
constexpr float SIN_PERIOD = 60.0f;		//�T�C���J�[�u����
constexpr VECTOR AXIS_Y = { 0.0f, 1.0f, 0.0f };
constexpr VECTOR AXIS_Z = { 0.0f, 0.0f, 1.0f };

EnemyShoot::EnemyShoot(EnemyType type,Vector3 pos, int number)
{
	type_ = type;
	initPos_ = pos;
	number_ = number;
	Init();
}

EnemyShoot::~EnemyShoot()
{
}

bool EnemyShoot::Init()
{
	auto rotY = Deg2RadF(90.0f);
	pos_ = initPos_;
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, rotY, 0.0f));

	count_ = 0.0f;
	state_ = State::Idle;
	alive_ = true;
	dir_ = DIR::LEFT;
	goalRot_ = Quaternion(1.0, 0.0, rotY, 0.0);
	stepRotTime_ = 0.0f;

	//�ʒu�E��]�B�傫�����
	auto matPos = MGetTranslate((pos_ + Vector3{ 0.0f, sin(DX_PI_F * 2.0f / SIN_PERIOD * count_) * MOVE_SPEED, 0.0f }).toVECTOR());
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetScale(VGet(0.5f, 0.5f, 0.5f)));
	Quaternion q = trans_.quaRot.Mult(trans_.quaRotLocal);
	mat = MMult(mat, q.ToMatrix());
	mat = MMult(mat, matPos);
	MV1SetMatrix(lpModelMng.GetID("./source/Model/Enemy/shoot_Enemy.mv1")[number_], mat);

	//�����G�t�F�N�g
	explosion_.resource = LoadEffekseerEffect("./source/effect/explosion.efkefc",25.0f);
	explosion_.playhandle = -1;

	//�e
	bullet_ = std::make_shared<BulletManager>();

	return false;
}


void EnemyShoot::Update(void)
{
}

void EnemyShoot::Update(std::vector<std::shared_ptr<Player>>& player)
{
	//�v���C���[�̈ʒu�X�V
	playerPos_ = player[0]->GetPos();

	//�e�ړ�
	bullet_->Move();

	if (player[0]->GetState() == State::Death)
	{
		alive_ = true;
		pos_ = initPos_;
	}
	//�͈͊O�̏ꍇ�A���������Ȃ�
	if (!CheckWithinRange(pos_, player[0]->GetPos()) || !alive_)
	{
		return;
	}

	//���˂��ꂽ�e�����������ꍇ�A�Փ˔��������
	for (auto& bullet : bullet_->GetBulletVector())
	{
		if (bullet->GetInversionFlag())
		{
			//�����蔻��
			if (CollisionSphere()(pos_, SPHERE_SIZE, "./source/Model/Enemy/bullet.mv1", bullet->GetNumber()))
			{
				explosion_.playhandle = PlayEffekseer3DEffect(explosion_.resource);
				explosion_.pos = pos_;
				alive_ = false;
				lpSoundMng.PlayingSound("./source/Sound/EnemyDeath.mp3");
				break;
			}
		}
	}

	//��]
	Rotate();

	//�X�V
	auto matPos = MGetTranslate((pos_ + Vector3{ 0.0f, sin(count_ / 50.0f) * MOVE_SPEED, 0.0f }).toVECTOR());
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetScale(VGet(0.5f, 0.5f, 0.5f)));
	Quaternion q = trans_.quaRot.Mult(trans_.quaRotLocal);
	mat = MMult(mat, q.ToMatrix());
	mat = MMult(mat, matPos);
	MV1SetMatrix(lpModelMng.GetID("./source/Model/Enemy/shoot_Enemy.mv1")[number_], mat);

	//�T�C���J�[�u�X�V
	count_ += 1.0f;

	//�e����
	bullet_->Create(playerPos_, pos_);

	SetPosPlayingEffekseer3DEffect(explosion_.playhandle, explosion_.pos.x, explosion_.pos.y, explosion_.pos.z);
}

void EnemyShoot::Draw(void)
{
	//�e
	bullet_->Draw();
	//�͈͊O�̏ꍇ�A���������Ȃ�
	if (!CheckWithinRange(pos_,playerPos_)||!alive_)
	{
		return;
	}
	//�G�̕`��
	MV1DrawModel(lpModelMng.GetID("./source/Model/Enemy/shoot_Enemy.mv1")[number_]);
}

Vector3 EnemyShoot::GetPosition(void)
{
	return pos_;
}

std::string EnemyShoot::GetHandlePath(void)
{
	std::string str = "./source/Model/Enemy/shoot_Enemy.mv1";
	return str;
}

EnemyType EnemyShoot::GetEnemyType(void)
{
	return type_;
}

bool EnemyShoot::GetisAlive(void)
{
	return alive_;
}

std::shared_ptr<BulletManager> EnemyShoot::GetBulletData(void)
{
	return bullet_;
}

void EnemyShoot::Rotate(void)
{
	Vector3 vec = (playerPos_ - pos_).Normalized();

	//�v���C���[�̕����ɉ�]����
	Quaternion rotZ;
	//�p�x��90�x�𒴂����ꍇ�͔��]������
	if (abs(Rad2DegF(atan2(-vec.y, -vec.x))) < 90.0f)
	{
		//������
		if (dir_ != DIR::LEFT)
		{
			dir_ = DIR::LEFT;
			goalRot_ = AngleAxis(Deg2RadF(90.0f), AXIS_Y);
			stepRotTime_ = ROT_TIME;
		}
		rotZ = AngleAxis(atan2(-vec.y, -vec.x), AXIS_Z);
	}
	else
	{
		//�E����
		if (dir_ != DIR::RIGHT)
		{
			dir_ = DIR::RIGHT;
			goalRot_ = AngleAxis(Deg2RadF(-90.0f), AXIS_Y);
			stepRotTime_ = ROT_TIME;
		}
		rotZ = AngleAxis(atan2(vec.y, vec.x), AXIS_Z);
	}

	//��Ԃ��ĉ�]
	trans_.quaRotLocal = trans_.quaRotLocal.Slerp(goalRot_, (ROT_TIME - stepRotTime_) / ROT_TIME);
	trans_.quaRot = trans_.quaRot.Slerp(rotZ, (ROT_TIME - stepRotTime_) / ROT_TIME);

	stepRotTime_ -= lpSceneMng.GetDeltaTime();
}
