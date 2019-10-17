#include "Input.h"

Input::Input()
{
	GM = nullptr;
}

Input::Input(GameMode* _GM)
{
	GM = _GM;
}

bool Input::Left()
{
	return false;
}

bool Input::Right()
{
	return false;
}

bool Input::Fire()
{
	return false;
}
