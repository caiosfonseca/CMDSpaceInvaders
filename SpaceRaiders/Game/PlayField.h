#pragma once

#include <vector>
#include "../Utils/Vector2D.h"

class GameObject;
class Input;
class GameMode;
class Alien;

class PlayField
{
private:
	std::vector<GameObject*> GameObjects;
	std::vector<GameObject*> GameObjectsAddQueue;
	std::vector<GameObject*> GameObjectsRemoveQueue;
	GameObject* PlayerObject;
	GameMode* GM;

public:
	Input* ControllerInput;
	Vector2D Bounds;
	// Number of available active laser slots for aliens and player
	int CurrentAlienLasers = 0;
	int MaxAlienLasers = 10;
	int CurrentPlayerLasers = 0;
	int MaxPlayerLasers = 10;
	int NOfAliensAlive = 0;
	int SpawnCycleCounter = 0;
	int LastAlienWaveSize = 5;
	int CurrentAlienWaveSize = 5;
	
	PlayField();
	PlayField(Vector2D _Bounds);
	PlayField(Vector2D _Bounds, GameObject* _PlayerObject);
	const std::vector<GameObject*>& GetGameObjects();

	void Update();

	GameObject* GetPlayerObject();
	void SetPlayerObject(GameObject* Player);

	GameMode* GetGameMode();
	void SetGameMode(GameMode* _GM);

	void SpawnLaser(GameObject* newObj);
	void DespawnLaser(GameObject* newObj);

	void AddObjectToAddQueue(GameObject* newObj);
	void AddObjectToRemoveQueue(GameObject* newObj);
	void AddObjectsToGame();
	void RemoveObjectsFromGame();

	void CreateExplosion(GameMode* GM, Vector2D Pos);
	void DecreaseAliens();
	void KillAlien(Alien* ET);
	void CreatePowerUp(GameMode* GM, Vector2D Pos);
	void KillPlayer();
	void SpawnAlienWave();
	void SpawnBlockingWalls();
};

