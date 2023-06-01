#pragma once
#include "../common/Vector2.h"
#include <memory>
#include <string>
#include <list>
#include "../../tmx/TmxObj.h"
#include "../Input/Controller.h"
class Torch;
class Simultaneous;
class Obj; 
class Door;
struct Collide;
struct CollideS;
struct Checkdie;
struct CheckCollUnitLR;
struct CheckCollUnitUD;
struct CheckCollUnitLRSP;
struct CheckCollUnitUDSP;
class Respawn;
struct CheckKeyLR;
struct CheckKeyUD;
struct CheckKeyLRSP;
struct TitleCheckObjR;
struct TitleCheckObjRSP;
struct PlayerhintHit;
using ObjUlist= std::list<std::unique_ptr<Obj>>;
//using ObjSlist = std::list<std::shared_ptr<Obj>>;
using uniCon = std::unique_ptr< Controller>;

static constexpr double square_size = 48.0;
static constexpr float Move_slowlyCnt = 1.4f;
static constexpr double Objoffset = 20.0;
static constexpr int VolumeObjSE = 100;
enum class DIR_LR
{
	NON,
	L,
	R,
	MAX
};

enum class MOVE_DIRECTION
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	MAX
};
enum class objType
{
	Player,
	Supporter,
	Hole,
	Half,
	Respawn,
	Door,
	DoorOpen,
	Torch,
	Goal,
	Simultaneous,
	Simultaneousdoor,
	PushDoor,
	Pushbutton,
	ThornPath,
	hint,
	OneWay,
	Max
 };
class Obj
{
public:
	Obj();
	virtual~Obj();
	virtual bool Init() = 0;
	virtual bool Init(double x, double y,bool die) = 0 ;
	virtual void Updata(TmxObj& tmxObj_, ObjUlist& objList_) = 0;
	virtual void Updata(TmxObj& tmxObj_, ObjUlist& objList_,double offset) {};
	virtual void Draw(void);
	virtual objType GetObjType(void) = 0;
	bool moveStop_checkdie_flag;
	bool GameOverMove_flag;
	MOVE_DIRECTION Moveabledir;
private:


protected:
	Vector2Dbl pos_;
	Vector2Dbl size_;
	int speed_;
	uniCon controller_;
	//�L�����N�^�[�̌�������
	DIR_LR moveLR;
	//�X�N���[���T�C�Y
	Vector2 screenSize_;
	//�����J���ۂ̂�����蓮������
	double OpenOldpos_;
	double CloseOldpos_;
	Vector2Dbl OriginalPos_;

	objType Obtype_;
	//�������Ɂ[�P������
	int die_alive_Cnt;//�M�~�b�N�����ʂ��Ƃ̂ł��鐔
	//�ړ�����
	MOVE_DIRECTION dir_;
	friend CheckKeyUD;
	friend CheckKeyLR;
	friend CheckKeyLRSP;
	friend Respawn;
	friend CheckCollUnitLR;
	friend CheckCollUnitUD;
	friend CheckCollUnitLRSP;
	friend CheckCollUnitUDSP;
	friend Checkdie;
	friend Torch;
	friend Door;
	friend Collide;
	friend CollideS;
	friend Simultaneous;
	friend TitleCheckObjR;
	friend TitleCheckObjRSP;
	friend PlayerhintHit;
};

