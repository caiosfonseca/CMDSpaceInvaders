#pragma once
#include "Input.h"

class RndInput : public Input
{
public:

	RndInput();
	RndInput(GameMode* _GM);

	virtual bool Left() override;
	virtual bool Right() override;
	virtual bool Fire() override;
};

