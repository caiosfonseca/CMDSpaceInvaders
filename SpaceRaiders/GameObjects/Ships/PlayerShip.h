#pragma once
#include <map>
#include "../GameObject.h"
#include "../PowerUps/PowerUp.h"

class PlayerShip : public GameObject
{
public:
	PlayerShip();
	PlayerShip(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Player_Ship, unsigned char _Sprite = RaiderSprites::RS_Player);

	void Update(PlayField& world) override;
	virtual bool DecreaseHealth(PlayField& world) override;

	void AddUpdateActivePower(PowerType Power, int Duration);
	int GetActivePowerDuration(PowerType Power);
	void CountDownActivePowers();
	std::string GetActivePowers();

private:
	std::map<PowerType, int> ActivePowers;
	float InitialVelocity = 1.f;
	float CurrentVelocity = 1.f;
	float BoostedFactor = 2.f;
	float FireRate = 1.f;

};

