#include "RndInput.h"

RndInput::RndInput() : Input()
{
}

RndInput::RndInput(GameMode* _GM) : Input(_GM)
{
}

bool RndInput::Left()
{
	floatRand keyRate(0, 1); 
	return (keyRate(GM->rGen) < 0.3f);
}

bool RndInput::Right()
{
	floatRand keyRate(0, 1); 
	return (keyRate(GM->rGen) < 0.4f);
}

bool RndInput::Fire()
{
	floatRand keyRate(0, 1); 
	return (keyRate(GM->rGen) < 0.5f);
}
