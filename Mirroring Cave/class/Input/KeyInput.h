#pragma once
#include "Controller.h"
#include <array>
#include <vector>


class KeyInput :
    public Controller
{
public:
	KeyInput();
	~KeyInput();
	void  Updata()override;
	CntTupe GetCntType(void)override {
		return CntTupe::Key;
	};

private:
	
protected:
	std::map<InputID, unsigned int>keyTbl_;
	//char keyData_[256];
	std::array<char, 256U> keyData_;//è„Ç≈Ç‡Ç¢Ç¢ÇØÇ«ÅAó˚èKÇ≈array
	/*cmm command;*/
	
};

