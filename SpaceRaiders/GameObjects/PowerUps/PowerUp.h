#pragma once
#include "../GameObject.h"

enum PowerType {
	PT_SpeedBoost,
	PT_FireRateBoost,
	PT_TripleFire
};

class PowerUp :	public GameObject
{
public:

	PowerUp();
	PowerUp(GameMode* _GM, Vector2D _Pos = Vector2D(), PowerType _Power = PowerType::PT_FireRateBoost, int _Duration = 100, unsigned char _Sprite = 'Z', ObjectType _ObjType = ObjectType::OT_PowerUp);

	virtual void Update(PlayField& world) override;

	void SetVerticalDirection(float _VerticalDirection);
	float GetVerticalDirection();

	void SetVelocity(float _Velocity);
	float GetVelocity();

	void SetDuration(int _Duration);
	int GetDuration();

	void SetPower(PowerType _Power);
	PowerType GetPower();

	virtual void MoveToDownwards(PlayField& world);
	virtual bool CheckBounds(PlayField& world);
	virtual bool CheckCollision(PlayField& world);

	static unsigned char GetSpriteFromType(PowerType _power);

private:
	PowerType Power;
	int Duration = 100;
	float VerticalDirection = 1.f;
	float Velocity = 0.5f;
};

