#pragma once
#include "Obj.h"
#include "AnimMng.h"
#include "../../tmx/TmxObj.h"
#include "../common/Raycast.h"

struct CheckCollUnitLR;
struct CheckCollUnitUD;
struct Move;
struct Checkdead;
struct SetAnime;
struct CheckState;
struct CheckCol;
struct CheckColUD;
struct CheckColD;
struct Collide;
struct TitleCheckObjR;
struct Checkflag;

class Player :
	public Obj
{
public:
	static constexpr int ShadowSize = 7;//影のオフセット
	Player();
	Player(double x, double y, bool die);
	Player(double x, double y, bool die, ObjUlist& list);
	~Player();
	 
private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_, double offset)override;
	void Draw(void)override;
	void PlaySE();
	 objType GetObjType(void)override
	 {
		 return objType::Player;
	 };
	 
	 Raycast raycast_;
	animItrCnt animItrCnt_;
	std::vector<char>stateVec_;
	rapidxml::xml_node<>* stateNode_;
	rapidxml::xml_document<> stateDoc;
	std::vector<char>TitlestateVec_;
	rapidxml::xml_node<>* TitlestateNode_;
	rapidxml::xml_document<> TitlestateDoc;

	bool CheckTitleHit_;
	int TitleHitCnt_;

	ObjUlist HintList_;

protected:
	int RoadSE_;		//道の効果音
	friend Collide;

	friend CheckCollUnitLR;
	friend CheckCollUnitUD;
	friend Move;

	friend CheckState;
	friend SetAnime;
	friend CheckCol;
	friend CheckColUD;
	friend CheckColD;
	friend TitleCheckObjR;
	friend Checkflag;

	friend Checkdead;
};

