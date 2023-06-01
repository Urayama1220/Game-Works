#pragma once
#include "Controller.h"
class PadInput :
    public Controller
{
public:
	PadInput();
	virtual ~PadInput();
	void  Updata() override;
	CntTupe GetCntType(void)override {
		return CntTupe::Pad;
	};
private:

protected:
	std::map<InputID, unsigned int>padTbl_;

};

