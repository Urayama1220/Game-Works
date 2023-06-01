#pragma once
#include "Obj.h"

class title :
	public Obj
{
public:
	
	title();
	title(double x, double y, bool die);
	~title();

private:
	bool Init()override;
	bool Init(double x, double y, bool die)override;
	void Updata(TmxObj& tmxObj_, ObjUlist& objList_)override;
	void Draw(void)override;
	float objTitleCnt_;
};

