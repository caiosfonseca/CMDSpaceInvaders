#pragma once
#include "Input.h"

class InputController : public Input
{
public:

	InputController();
	InputController(GameMode* _GM);

	virtual bool Left() override;
	virtual bool Right() override;
	virtual bool Fire() override;
};

