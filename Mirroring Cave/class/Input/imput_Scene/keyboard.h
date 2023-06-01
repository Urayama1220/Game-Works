#pragma once
#include "Imput.h"
class keyboard :
	public Imput
{
public:
	keyboard();
	~keyboard();
private:
	bool Updata()override;
	bool init(void);
	
protected:
	std::map<std::string, int>keyTbl_;
	char keyData_[256];
};

