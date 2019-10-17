#include "AlienLaser.h"
#include "../FX/Explosion.h"
#include "../../Game/PlayField.h"

AlienLaser::AlienLaser() : Laser()
{
}

AlienLaser::AlienLaser(GameMode* _GM, Vector2D _Pos, Vector2D _Direction, ObjectType _ObjType, unsigned char _Sprite) : Laser(_GM, _Pos, _Direction, _ObjType, _Sprite)
{
}

void AlienLaser::Update(PlayField& world)
{
	Laser::Update(world);
}

bool AlienLaser::CheckBounds(PlayField& world)
{
	if (Pos.y > world.Bounds.y)
	{
		return true;
	}
	return false;
}

bool AlienLaser::CheckCollision(PlayField& world)
{
	GameObject* player = world.GetPlayerObject();
	if (player && Pos.IntCmp(player->Pos))
	{		
		player->DecreaseHealth(world);
		return true;
	}
	return false;
}
