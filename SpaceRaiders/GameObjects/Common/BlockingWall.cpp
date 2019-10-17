#include "BlockingWall.h"
#include "../../Game/PlayField.h"

BlockingWall::BlockingWall() : GameObject()
{
	SetHealth(2.f);
}

BlockingWall::BlockingWall(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
	SetHealth(2.f);
}

bool BlockingWall::DecreaseHealth(PlayField& world)
{
	SetHealth(GetHealth() - 1);
	if (GetHealth() <= 0)
	{
		world.AddObjectToRemoveQueue(this);

		return true;
	}
	return false;
}
