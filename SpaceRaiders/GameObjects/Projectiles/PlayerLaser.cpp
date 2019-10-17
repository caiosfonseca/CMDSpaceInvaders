#include "PlayerLaser.h"
#include "../FX/Explosion.h"
#include "../../Game/PlayField.h"
#include "../PowerUps/PowerUp.h"


PlayerLaser::PlayerLaser() : Laser()
{
}

PlayerLaser::PlayerLaser(GameMode* _GM, Vector2D _Pos, Vector2D _Direction, ObjectType _ObjType, unsigned char _Sprite) : Laser(_GM, _Pos, _Direction, _ObjType, _Sprite)
{
}

void PlayerLaser::Update(PlayField& world)
{
	Laser::Update(world);
}

bool PlayerLaser::CheckBounds(PlayField& world)
{
	if (Pos.y < 0)
	{
		return true;
	}
	return false;
}

bool PlayerLaser::CheckCollision(PlayField& world)
{
	for (auto it : world.GetGameObjects())
	{
		if ((it->ObjType == ObjectType::OT_Alien_Ship || it->ObjType == ObjectType::OT_Alien_Ship_Better || it->ObjType == ObjectType::OT_BlockingWall) && it->Pos.IntCmp(Pos))
		{
			world.CreateExplosion(GM, Pos);
			it->DecreaseHealth(world);
			return true;
		}
	}
	return false;
}