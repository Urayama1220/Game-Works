#pragma once
#include "Obj.h"
#include "AnimMng.h"
#include "../../tmx/TmxObj.h"
#include "../common/Raycast.h"

struct MoveSP;
struct CheckKeyUDSP;
struct SetAnimeSP;
struct CheckStateSP;
struct CheckColSP;
struct CheckColUSP;
struct CheckColDSP;
struct CheckCollUnitLRSP;
struct CheckCollUnitUDSP;
struct TitleCheckObjRSP;
struct CheckflagSP;
class Supporter :
	public Obj
{
public:
	Supporter();
	Supporter(double x, double y, bool die);
	~Supporter();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_, double offset)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Supporter;
	};
	int BoxSE_;		//“¹‚ÌŒø‰Ê‰¹
	bool SE_;	//	SE‚ð–Â‚ç‚·ƒtƒ‰ƒO
	animItrCnt animItrCnt_;

	Raycast raycast_;

	std::vector<char>stateVec_;
	rapidxml::xml_node<>* stateNode_;
	rapidxml::xml_document<> stateDoc;


	std::vector<char>TitlestateVec_;
	rapidxml::xml_node<>* TitlestateNode_;
	rapidxml::xml_document<> TitlestateDoc;

	bool CheckTitleHitSP_;
	int TitleHitCntSP_;

	friend MoveSP;
	friend CheckKeyUDSP;
	friend CheckStateSP;
	friend SetAnimeSP;
	friend CheckColSP;
	friend CheckColUSP;
	friend CheckColDSP;
	friend CheckCollUnitLRSP;
	friend CheckCollUnitUDSP;
	friend TitleCheckObjRSP;
	friend CheckflagSP;

};

