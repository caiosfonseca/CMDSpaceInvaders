#pragma once
#include "../GameObject.h"

class Laser : public GameObject
{
public:
	Vector2D Direction;

	Laser();
	Laser(GameMode* _GM, Vector2D _Pos = Vector2D(), Vector2D _Direction = Vector2D(0.f,-1.f), ObjectType _ObjType = ObjectType::OT_Laser_Alien, unsigned char _Sprite = RaiderSprites::RS_AlienLaser);

	virtual void Update(PlayField& world);
	virtual void MoveToDirection(PlayField& world);
	virtual bool CheckBounds(PlayField& world);
	virtual bool CheckCollision(PlayField& world);
};

