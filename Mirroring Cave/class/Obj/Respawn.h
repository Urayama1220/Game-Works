#pragma once
#include "Obj.h"
class Respawn :
	public Obj
{
public:
	Respawn();
	Respawn(double x, double y, bool die);
	~Respawn();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	objType GetObjType(void)override
	{
		return objType::Respawn;
	};
	int ReCnt_;	//ƒŠƒXƒ|[ƒ“‰ñ”
};

