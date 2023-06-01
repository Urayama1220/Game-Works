#pragma once
#include <string>
#include "Obj.h"
class hint :
    public Obj
{
public:
	hint();
	hint(double x, double y, bool die,std::string hintId);
	hint(double x, double y, bool die, std::string hintId , Vector2Dbl Addsize);
	~hint();

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
	std::string hintId_;
	Vector2Dbl sizeAdd_;
};

