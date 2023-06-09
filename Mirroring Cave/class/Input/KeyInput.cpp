#include "KeyInput.h"
#include <Dxlib.h>

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
KeyInput::KeyInput()
{
	keyTbl_ = {			// ２個セットだったら{}を付けておく		keyTbl_に２個１で格納
		{InputID::Up,KEY_INPUT_UP},
		{InputID::Down,KEY_INPUT_DOWN},
		{InputID::Left,KEY_INPUT_LEFT},
		{InputID::Right,KEY_INPUT_RIGHT},
		{InputID::Btn1,KEY_INPUT_Z},
		{InputID::Btn2,KEY_INPUT_X},
		{InputID::Btn3,KEY_INPUT_C},
		{InputID::Esc,KEY_INPUT_ESCAPE}


	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0,0 });
	}
	
	
}

KeyInput::~KeyInput()
{
}

void  KeyInput::Updata()
{

	GetHitKeyStateAll(keyData_.data());
	/*cntData_[InputID::Up][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[InputID::Up]];		//これをまとめてやりたい
	auto id = InputID::Up;
	cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[id]];*/		//idでまとめた
	for (auto id : InputID())												//InpoutID.hを作って範囲for文を回せるようにした
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[id]];




	}

}


