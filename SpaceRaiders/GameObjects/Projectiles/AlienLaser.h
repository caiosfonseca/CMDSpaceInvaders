#pragma once
#include "Laser.h"

class AlienLaser : public Laser
{
public:
	AlienLaser();
	AlienLaser(GameMode* _GM, Vector2D _Pos = Vector2D(), Vector2D _Direction = Vector2D(0.f, 1.f), ObjectType _ObjType = ObjectType::OT_Laser_Alien, unsigned char _Sprite = RaiderSprites::RS_AlienLaser);

	void Update(PlayField& world) override;
	bool CheckBounds(PlayField& world) override;
	bool CheckCollision(PlayField& world) override;
};