#include "keyboard.h"
#include <Dxlib.h>

keyboard::keyboard()
{
	init();
}

keyboard::~keyboard()
{
}

bool keyboard::Updata()
{
	for (auto& data:data_)
	{
		dataOld_[data.first] = data.second;
	}
	GetHitKeyStateAll(keyData_);
	for (auto tblData : keyTbl_)
	{
		data_[tblData.first] = keyData_[tblData.second];
	}
	return true;//false����
	//data_["��"] = keyData_[keyTbl_["��"]];				�{�^��������΂���͏�Ɠ���
}

bool keyboard::init(void)
{

	keyTbl_["��"]= KEY_INPUT_UP;
	keyTbl_["��"] = KEY_INPUT_DOWN;
	keyTbl_["��"] = KEY_INPUT_LEFT;
	keyTbl_["�E"] = KEY_INPUT_RIGHT;
	keyTbl_["A"] = KEY_INPUT_Z;
	keyTbl_["�G�f�B�b�g"] = KEY_INPUT_F6;
	keyTbl_["Esc"] = KEY_INPUT_ESCAPE;
	

	for (auto tblData : keyTbl_)
	{
		data_.emplace(tblData.first, 0);
	}
	
	return true;
}
