#include "PlayField.h"
#include "../GameObjects/GameObject.h"
#include "../Controllers/Input.h"
#include "../Controllers/RndInput.h"
#include "../GameObjects/Projectiles/PlayerLaser.h"
#include "../GameObjects/Ships/Alien.h"
#include "../GameObjects/PowerUps/PowerUp.h"
#include "../GameObjects/FX/Explosion.h"
#include "../GameObjects/Common/BlockingWall.h"


PlayField::PlayField()
{
	Bounds = Vector2D(80.0f, 40.0f);
	PlayerObject = nullptr;
	ControllerInput = nullptr;
	GM = nullptr;
	NOfAliensAlive = 0;
}

PlayField::PlayField(Vector2D _Bounds)
{
	PlayField();
	Bounds = _Bounds;
}

PlayField::PlayField(Vector2D _Bounds, GameObject* _PlayerObject)
{
	PlayField();
	Bounds = _Bounds;
	PlayerObject = _PlayerObject;
}

const std::vector<GameObject*>& PlayField::GetGameObjects()
{
	return GameObjects;
}

void PlayField::Update()
{
	for (GameObject* it : GameObjects)
	{
		if (it != nullptr)
		{
			it->Update(*this);
		}
	}

	if (GM->GT == GameType::GT_Endless)
	{
		if (SpawnCycleCounter == 0)
		{
			for (int k = 0; k < GM->MaxNOfAliens; k++)
			{
				Alien* a = new Alien(GM, Vector2D(k*3.f, 0.f));
				AddObjectToAddQueue(a);
			}
		}
		SpawnCycleCounter = (SpawnCycleCounter + 1) % 180;
	}

	RemoveObjectsFromGame();
	AddObjectsToGame();
}

GameObject* PlayField::GetPlayerObject()
{
	if (PlayerObject != nullptr)
	{
		return PlayerObject;
	}
	else
	{
		auto it = std::find_if(GameObjects.begin(), GameObjects.end(), [](GameObject* in) { return in->ObjType == ObjectType::OT_Player_Ship; });
		if (it != GameObjects.end())
		{
			return (*it);
		}			
	}
	return nullptr;
}

void PlayField::SetPlayerObject(GameObject* Player)
{
	PlayerObject = Player;
}

GameMode* PlayField::GetGameMode()
{
	return GM;
}

void PlayField::SetGameMode(GameMode* _GM)
{
	GM = _GM;
}

void PlayField::SpawnLaser(GameObject* newObj)
{
	if (newObj->ObjType == ObjectType::OT_Laser_Alien)
	{
		CurrentAlienLasers++;
	}		
	else if (newObj->ObjType == ObjectType::OT_Laser_Player)
	{
		if (((PlayerLaser*)newObj)->Direction.x == 0)
		{
			CurrentPlayerLasers++;
		}
	}		
	AddObjectToAddQueue(newObj);
}

void PlayField::DespawnLaser(GameObject* newObj)
{
	if (newObj->ObjType == ObjectType::OT_Laser_Alien)
	{
		CurrentAlienLasers--;
	}
	else if (newObj->ObjType == ObjectType::OT_Laser_Player)
	{
		if (((PlayerLaser*)newObj)->Direction.x == 0)
		{
			CurrentPlayerLasers--;
		}
	}
	AddObjectToRemoveQueue(newObj);
}

void PlayField::AddObjectToAddQueue(GameObject* newObj)
{
	GameObjectsAddQueue.push_back(newObj);
}

void PlayField::AddObjectsToGame()
{
	for (GameObject* it : GameObjectsAddQueue)
	{
		GameObjects.push_back(it);
	}

	GameObjectsAddQueue.clear();

}

void PlayField::AddObjectToRemoveQueue(GameObject* newObj)
{
	GameObjectsRemoveQueue.push_back(newObj);
}

void PlayField::RemoveObjectsFromGame()
{
	for (GameObject* it : GameObjectsRemoveQueue)
	{
		auto tempIt = std::find_if(GameObjects.begin(), GameObjects.end(), [&](GameObject* in) { return (in == it); });
		GameObjects.erase(tempIt);
	}

	GameObjectsRemoveQueue.clear();
}

void PlayField::CreateExplosion(GameMode* GM, Vector2D Pos)
{
	GameObject& exp = *(new Explosion(GM, Pos));
	AddObjectToAddQueue(&exp);
}

void PlayField::DecreaseAliens()
{
	NOfAliensAlive--;
	if (NOfAliensAlive == 0)
	{
		if (GM->GT == GameType::GT_Default)
		{
			GM->GS = GameState::GS_GameOver;
		}
		else if(GM->GT == GameType::GT_Waves)
		{
			GM->GS = GameState::GS_WaveFinished;
			SpawnAlienWave();
			SpawnBlockingWalls();
			GM->GS = GameState::GS_Playing;
		}
	}
}

void PlayField::KillAlien(Alien* ET)
{
	GM->IncreaseScore(ET);

	CreatePowerUp(GM, ET->Pos);

	AddObjectToRemoveQueue(ET);
}

void PlayField::CreatePowerUp(GameMode* GM, Vector2D Pos)
{
	floatRand powerUpRate(0, 1);
	float powerUpType = 0.f;
	PowerType type;
	if (powerUpRate(GM->rGen) < GM->PowerUpRate)
	{
		powerUpType = powerUpRate(GM->rGen);
		if (powerUpType < 0.33f)
		{
			type = PowerType::PT_FireRateBoost;
		}
		else if (powerUpType < 0.66f)
		{
			type = PowerType::PT_SpeedBoost;
		}
		else
		{
			type = PowerType::PT_TripleFire;
		}
		//Spawn laser
		GameObject& newPowerUp = *(new PowerUp(GM, Pos, type, 100, PowerUp::GetSpriteFromType(type)));
		AddObjectToAddQueue(&newPowerUp);
	}
}

void PlayField::KillPlayer()
{
	CreateExplosion(GM, PlayerObject->Pos);
	AddObjectToRemoveQueue(PlayerObject);
	GM->GS = GameState::GS_GameOver;
}

void PlayField::SpawnAlienWave()
{
	intRand xCoord(0, (int)GM->MapSize.x - 1);
	intRand yCoord(0, 10);

	LastAlienWaveSize = CurrentAlienWaveSize;
	CurrentAlienWaveSize = GM->GT == GameType::GT_Default ? GM->MaxNOfAliens : LastAlienWaveSize;

	for (int k = 0; k < CurrentAlienWaveSize; k++)
	{
		Alien* a = new Alien(GM, Vector2D((float)xCoord(GM->rGen), (float)yCoord(GM->rGen)));
		AddObjectToAddQueue(a);
	}

	NOfAliensAlive = CurrentAlienWaveSize;
	if (CurrentAlienWaveSize < GM->MaxNOfAliens )
	{
		CurrentAlienWaveSize += 2;
		if (CurrentAlienWaveSize > GM->MaxNOfAliens)
		{
			CurrentAlienWaveSize = GM->MaxNOfAliens;
		}
	}
	GM->CurrentWave++;
}

void PlayField::SpawnBlockingWalls()
{
	intRand xCoord(0, (int)GM->MapSize.x - 1);
	intRand yCoord(0, 10);

	int wallCount = 1 + (CurrentAlienWaveSize / 3);

	for (int k = 0; k < wallCount; k++)
	{
		BlockingWall* a = new BlockingWall(GM, Vector2D((float)xCoord(GM->rGen), (float)yCoord(GM->rGen)));
		AddObjectToAddQueue(a);
	}
}


