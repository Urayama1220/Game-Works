#pragma once
#include<type_traits>

enum class InputID
{
	NON,
	Up,
	Down,
	Left,
	Right,
	Btn1,
	Btn2,
	Btn3,
	Esc,
	Max
};


static InputID begin(InputID) {
	return InputID::Up;
};

static InputID end(InputID) {
	return InputID::Max;
};
//auto sdkfj = std::underlying_type<InputID>::type(state) int‚ªæ‚ê‚Ä‚¢‚é
static InputID operator++(InputID& state) {
	state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1);	//InputID‚Ì‹K’è‚ÌŒ^‚ğ‚µ‚ç‚×‚Ä‚»‚¢‚Â‚ğˆø‚Á’£‚Ä‚«‚Ä{‚P‚µ‚Ä‚¢‚é
	return state;
};
static InputID operator*(InputID& state) {
	return state;
};