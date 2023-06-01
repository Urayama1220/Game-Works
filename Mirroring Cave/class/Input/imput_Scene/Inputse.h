#pragma once
#include <DxLib.h>
#include <memory>
#include "joypad.h"
#include "keyboard.h"

struct Inputse
{
	std::unique_ptr<Imput> operator()()
	{
		std::unique_ptr<Imput>imput;
		if (GetJoypadNum())
		{
			imput = std::make_unique<joypad>();
		}
		else
		{
			imput = std::make_unique<keyboard>();
		}
		return imput;
	}
};