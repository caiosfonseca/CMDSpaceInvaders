#include "PlayerShip.h"
#include "../Projectiles/PlayerLaser.h"
#include "../../Game/PlayField.h"
#include "../../Controllers/Input.h"
#include <sstream>

PlayerShip::PlayerShip() : GameObject()
{
}

PlayerShip::PlayerShip(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
}

void PlayerShip::Update(PlayField& world)
{
	CurrentVelocity = InitialVelocity * (GetActivePowerDuration(PowerType::PT_SpeedBoost) > 0 ? BoostedFactor : 1.0f);
	if (world.ControllerInput != nullptr)
	{
		if (world.ControllerInput->Left())
		{
			if (Pos.x > 0)
			{
				Pos.x -= CurrentVelocity;
			}			
		}
		else if (world.ControllerInput->Right())
		{
			if (Pos.x < world.Bounds.x - 1)
			{
				Pos.x += CurrentVelocity;
			}
		}	


		FireRate = GetActivePowerDuration(PowerType::PT_FireRateBoost) > 0 ? 2.0f : 1.0f;

		if (world.ControllerInput->Fire() && world.CurrentPlayerLasers < (world.MaxPlayerLasers * FireRate))
		{
			GameObject& newLaser = *(new PlayerLaser(GM, Pos));
			world.SpawnLaser(&newLaser);
			if (GetActivePowerDuration(PowerType::PT_TripleFire) > 0)
			{
				GameObject& newLaser = *(new PlayerLaser(GM, Pos, Vector2D(1.0, -1.0f)));
				world.SpawnLaser(&newLaser);
				GameObject& newLaser2 = *(new PlayerLaser(GM, Pos, Vector2D(-1.0, -1.0f)));
				world.SpawnLaser(&newLaser2);
			}
		}
	}
	CountDownActivePowers();
}

bool PlayerShip::DecreaseHealth(PlayField& world)
{
	SetHealth(GetHealth() - 1);
	if (GetHealth() <= 0)
	{
		world.KillPlayer();
		return true;
	}
	return false;
}

void PlayerShip::AddUpdateActivePower(PowerType Power, int Duration)
{
	ActivePowers[Power] = Duration;
}

int PlayerShip::GetActivePowerDuration(PowerType Power)
{
	int result = -1;
	if (ActivePowers.find(Power) != ActivePowers.end())
	{
		result = ActivePowers[Power];
	}
	return result;
}

void PlayerShip::CountDownActivePowers()
{
	int duration;
	for (std::pair<PowerType, int> p : ActivePowers)
	{
		if (p.second >= 0)
		{
			duration = p.second - 1;
			AddUpdateActivePower(p.first, duration);
		}
	}
}

std::string PlayerShip::GetActivePowers()
{
	std::stringstream ssm = std::stringstream();
	std::string result = "";
	char powerChar = ' ';
	for (std::pair<PowerType, int> p : ActivePowers)
	{
		switch (p.first)
		{
		case PowerType::PT_SpeedBoost:
			powerChar = RaiderSprites::RS_SpeedBoost;
			break;
		case PowerType::PT_FireRateBoost:
			powerChar = RaiderSprites::RS_FireRateBoost;
			break;
		case PowerType::PT_TripleFire:
			powerChar = RaiderSprites::RS_TripleFire;
			break;
		default:
			powerChar = 'P';
			break;
		}
		if (p.second > 0)
		{
			ssm << powerChar << "(" << std::to_string(p.second) << ") ";
		}
		else
		{
			ssm << "     ";
		}
	}
	result = ssm.str();
	return result;
}
