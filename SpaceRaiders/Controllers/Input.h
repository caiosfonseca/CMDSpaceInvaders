#pragma once

#include "../Game/GameMode.h"

class Input
{
public:

	GameMode* GM;

	Input();
	Input(GameMode* _GM);

	virtual bool Left();
	virtual bool Right();
	virtual bool Fire();
};

