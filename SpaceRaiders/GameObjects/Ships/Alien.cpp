#include "Alien.h"
#include "../Projectiles/AlienLaser.h"
#include "../FX/Explosion.h"
#include "../../Game/PlayField.h"
#include "BetterAlien.h"

Alien::Alien() : GameObject()
{
	SetHealth(1.f);
}

Alien::Alien(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
	SetHealth(1.f);
}

void Alien::Update(PlayField& world)
{
	Pos.x += HorizontalDirection * Velocity;
	// Border check
	if (Pos.x < 0 || Pos.x >= world.Bounds.x - 1)
	{
		HorizontalDirection = -HorizontalDirection;
		Pos.y += 1;
	}

	// Border check vertical:
	if (Pos.y >= world.Bounds.y - 1)
	{
		// kill player
		GameObject* player = world.GetPlayerObject();
		if (player && Pos.IntCmp(player->Pos))
		{
			//Spawn explosion
			world.CreateExplosion(GM, Pos);
			world.AddObjectToRemoveQueue(player);
		}
	}

	// Transform into better Alien
	if (ObjType == ObjectType::OT_Alien_Ship)
	{
		floatRand updateRate(-MaxUpdateRate, 2 * MaxUpdateRate);
		Energy += updateRate(GM->rGen);
		if (Energy >= TransformEnergy)
		{
			Transform(world);
		}
	}
	
	floatRand fireRate(0, 1);
	if (fireRate(GM->rGen) < 0.5 && world.CurrentAlienLasers < world.MaxAlienLasers)
	{
		//Spawn laser
		GameObject& newLaser = *(new AlienLaser(GM, Pos));
		world.SpawnLaser(&newLaser);
	}
}

void Alien::Transform(PlayField& world)
{
	GameObject& newAlien = *(new BetterAlien(HorizontalDirection, GM, Pos));
	world.AddObjectToAddQueue(&newAlien);
	world.AddObjectToRemoveQueue(this);
}

bool Alien::DecreaseHealth(PlayField& world)
{
	SetHealth(GetHealth() - 1);
	if (GetHealth() <= 0)
	{
		if (GM->GT != GameType::GT_Endless)
		{
			world.DecreaseAliens();
		}

		world.KillAlien(this);
		
		return true;
	}
	return false;
}

void Alien::SetDirection(float _Direction)
{
	HorizontalDirection = _Direction;
}

float Alien::GetDirection()
{
	return HorizontalDirection;
}

void Alien::SetEnergy(float _Energy)
{
	Energy = _Energy;
}

float Alien::GetEnergy()
{
	return Energy;
}

void Alien::SetVelocity(float _Velocity)
{
	Velocity = _Velocity;
}

float Alien::GetVelocity()
{
	return Velocity;
}
