#pragma once
#include<memory>
#include<vector>
#include"../../../Common/Geometry.h"
#include"Bullet.h"
#include"../../../Common/Raycast.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	//‰Šú‰»
	void Init(void);

	//XV
	void Create(Vector3 playerpos, Vector3 enemypos);

	//”jŠü
	void Release(void);

	//ˆÚ“®
	void Move(void);

	//’e‚Ì•`‰æ
	void Draw(void);

	//’e‚Æƒƒbƒh‚Ì”»’è
	void CollisionRodAndBullet(Line line,Line right,Line left);

	//’eî•ñæ“¾
	std::vector<std::shared_ptr<Bullet>>& GetBulletVector(void);

private:
	//’e‚Ì’è‹`
	std::vector<std::shared_ptr<Bullet>> bullets_;

	//’e‚Ì”­ËŠÔŠu
	double bulletFiringTime_;

	Raycast raycast_;

	//’e‚Ì”
	int bulletNum_;
};
