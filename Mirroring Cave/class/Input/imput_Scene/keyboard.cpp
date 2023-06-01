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
	return true;//falseかも
	//data_["上"] = keyData_[keyTbl_["上"]];				ボタン分つくればこれは上と同じ
}

bool keyboard::init(void)
{

	keyTbl_["上"]= KEY_INPUT_UP;
	keyTbl_["下"] = KEY_INPUT_DOWN;
	keyTbl_["左"] = KEY_INPUT_LEFT;
	keyTbl_["右"] = KEY_INPUT_RIGHT;
	keyTbl_["A"] = KEY_INPUT_Z;
	keyTbl_["エディット"] = KEY_INPUT_F6;
	keyTbl_["Esc"] = KEY_INPUT_ESCAPE;
	

	for (auto tblData : keyTbl_)
	{
		data_.emplace(tblData.first, 0);
	}
	
	return true;
}
