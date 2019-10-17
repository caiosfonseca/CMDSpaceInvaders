#include "InputController.h"
#include "Windows.h"

InputController::InputController() : Input()
{
}

InputController::InputController(GameMode* _GM) : Input(_GM)
{
}

bool InputController::Left()
{
	return GetAsyncKeyState(VK_LEFT) != 0;
}

bool InputController::Right()
{
	return GetAsyncKeyState(VK_RIGHT) != 0;
}

bool InputController::Fire()
{
	return GetAsyncKeyState(VK_SPACE) != 0;
}