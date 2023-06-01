#include "PadInput.h"
#include <DxLib.h>
PadInput::PadInput()
{
	padTbl_ = {			// ‚QŒÂƒZƒbƒg‚¾‚Á‚½‚ç{}‚ğ•t‚¯‚Ä‚¨‚­		keyTbl_‚É‚QŒÂ‚P‚ÅŠi”[
		{InputID::Up,PAD_INPUT_UP},
		{InputID::Down,PAD_INPUT_DOWN},
		{InputID::Left,PAD_INPUT_LEFT},
		{InputID::Right,PAD_INPUT_RIGHT},
		{InputID::Btn1,PAD_INPUT_1},
		{InputID::Btn2,PAD_INPUT_2},
		{InputID::Btn3,PAD_INPUT_3},


	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0,0 });
	}
	
}

PadInput::~PadInput()
{
	
}

void PadInput::Updata()
{
	auto inputData = GetJoypadInputState(DX_INPUT_PAD1);

	for (auto id : InputID())												//InpoutID.h‚ğì‚Á‚Ä”ÍˆÍfor•¶‚ğ‰ñ‚¹‚é‚æ‚¤‚É‚µ‚½
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = inputData & padTbl_[id];
	}
	
}
