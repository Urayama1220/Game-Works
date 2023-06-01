#include "KeyInput.h"
#include <Dxlib.h>

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
KeyInput::KeyInput()
{
	keyTbl_ = {			// ‚QŒÂƒZƒbƒg‚¾‚Á‚½‚ç{}‚ğ•t‚¯‚Ä‚¨‚­		keyTbl_‚É‚QŒÂ‚P‚ÅŠi”[
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
	/*cntData_[InputID::Up][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[InputID::Up]];		//‚±‚ê‚ğ‚Ü‚Æ‚ß‚Ä‚â‚è‚½‚¢
	auto id = InputID::Up;
	cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[id]];*/		//id‚Å‚Ü‚Æ‚ß‚½
	for (auto id : InputID())												//InpoutID.h‚ğì‚Á‚Ä”ÍˆÍfor•¶‚ğ‰ñ‚¹‚é‚æ‚¤‚É‚µ‚½
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyTbl_[id]];




	}

}


