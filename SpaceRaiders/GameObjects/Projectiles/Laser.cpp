#include "Laser.h"
#include "../FX/Explosion.h"
#include "../../Game/PlayField.h"

Laser::Laser() : GameObject()
{
}

Laser::Laser(GameMode* _GM, Vector2D _Pos, Vector2D _Direction, ObjectType _ObjType, unsigned char _Sprite) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
	Direction = _Direction;
}

void Laser::Update(PlayField& world)
{
	MoveToDirection(world);
	bool deleted = CheckBounds(world);

	if (!deleted)
	{
		deleted = CheckCollision(world);
	}

	if (deleted)
	{
		world.DespawnLaser((GameObject*)this);
		delete this;
	}
}

void Laser::MoveToDirection(PlayField& world)
{
	Pos.y += Direction.y;
	Pos.x += Direction.x;
}

bool Laser::CheckBounds(PlayField& world)
{
	if (Pos.y > world.Bounds.y)
	{
		return true;
	}
	return false;
}

bool Laser::CheckCollision(PlayField& world)
{
	return false;
}
