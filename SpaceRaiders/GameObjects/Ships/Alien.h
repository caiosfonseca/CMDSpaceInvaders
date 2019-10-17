#pragma once
#include "../GameObject.h"

class Alien : public GameObject
{
public:

	Alien();
	Alien(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Alien_Ship, unsigned char _Sprite = RaiderSprites::RS_Alien);

	virtual void Update(PlayField& world) override;
	void Transform(PlayField& world);
	virtual bool DecreaseHealth(PlayField& world) override;

	void SetDirection(float _Direction);
	float GetDirection();

	void SetEnergy(float _Energy);
	float GetEnergy();

	void SetVelocity(float _Velocity);
	float GetVelocity();

private:
	// Alien constants - these could move out into PlayField as configurable variables
	const float MaxUpdateRate = 0.01f;
	const float TransformEnergy = 1.f;
	// Variables dictating energy level for upgrade, direction of movement, and current speed
	float Energy = 0.f;
	float HorizontalDirection = 1.f;
	float Velocity = 0.5f;
};

