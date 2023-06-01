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
//auto sdkfj = std::underlying_type<InputID>::type(state) int�����Ă���
static InputID operator++(InputID& state) {
	state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1);	//InputID�̋K��̌^������ׂĂ������������Ă��ā{�P���Ă���
	return state;
};
static InputID operator*(InputID& state) {
	return state;
};