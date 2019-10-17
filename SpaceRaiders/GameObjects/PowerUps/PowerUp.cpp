#include "PowerUp.h"
#include "../../Game/PlayField.h"
#include "../Ships/PlayerShip.h"

PowerUp::PowerUp() : GameObject()
{
	Power = PowerType::PT_SpeedBoost;
	Duration = 100;
}

PowerUp::PowerUp(GameMode* _GM, Vector2D _Pos, PowerType _Power, int _Duration, unsigned char _Sprite, ObjectType _ObjType) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
	Power = _Power;
	Duration = _Duration;
}

void PowerUp::Update(PlayField& world)
{
	MoveToDownwards(world);
	bool deleted = CheckBounds(world);

	if (!deleted)
	{
		deleted = CheckCollision(world);
	}

	if (deleted)
	{
		world.AddObjectToRemoveQueue((GameObject*)this);
	}
}

void PowerUp::SetVerticalDirection(float _VerticalDirection)
{
	VerticalDirection = _VerticalDirection;
}

float PowerUp::GetVerticalDirection()
{
	return VerticalDirection;
}

void PowerUp::SetVelocity(float _Velocity)
{
	Velocity = _Velocity;
}

float PowerUp::GetVelocity()
{
	return Velocity;
}

void PowerUp::SetDuration(int _Duration)
{
	Duration = _Duration;
}

int PowerUp::GetDuration()
{
	return Duration;
}

void PowerUp::SetPower(PowerType _Power)
{
	Power = _Power;
}

PowerType PowerUp::GetPower()
{
	return Power;
}

void PowerUp::MoveToDownwards(PlayField& world)
{
	Pos.y += VerticalDirection * Velocity;
}

bool PowerUp::CheckBounds(PlayField& world)
{
	if (Pos.y > world.Bounds.y)
	{
		return true;
	}
	return false;
}

bool PowerUp::CheckCollision(PlayField& world)
{
	GameObject* player = world.GetPlayerObject();
	if (player && Pos.IntCmp(player->Pos))
	{
		((PlayerShip*)player)->AddUpdateActivePower(Power, Duration);
		return true;
	}
	return false;
}

unsigned char PowerUp::GetSpriteFromType(PowerType _power)
{
	unsigned char _sprite = ' ';
	switch (_power)
	{
	case PowerType::PT_SpeedBoost:
		_sprite = RaiderSprites::RS_SpeedBoost;
		break;
	case PowerType::PT_FireRateBoost:
		_sprite = RaiderSprites::RS_FireRateBoost;
		break;
	case PowerType::PT_TripleFire:
		_sprite = RaiderSprites::RS_TripleFire;
		break;
	default:
		_sprite = 'Z';
		break;
	}
	return _sprite;
}
