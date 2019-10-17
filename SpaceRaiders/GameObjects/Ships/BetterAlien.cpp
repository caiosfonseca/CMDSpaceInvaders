#include "BetterAlien.h"
#include "../Projectiles/AlienLaser.h"
#include "../FX/Explosion.h"
#include "../../Game/PlayField.h"

BetterAlien::BetterAlien() : Alien()
{
	Alien::SetHealth(2.f);
	Alien::SetVelocity(1.f);
}

BetterAlien::BetterAlien(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : Alien(_GM, _Pos, _ObjType, _Sprite)
{
	Alien::SetHealth(2.f);
	Alien::SetVelocity(1.f);
}

BetterAlien::BetterAlien(float _direction, GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : Alien(_GM, _Pos, _ObjType, _Sprite)
{
	Alien::SetHealth(2.f);
	Alien::SetVelocity(1.f);
	Alien::SetDirection(_direction);
}

void BetterAlien::Update(PlayField& world)
{
	Alien::Update(world);
}

bool BetterAlien::DecreaseHealth(PlayField& world)
{
	return Alien::DecreaseHealth(world);
}
