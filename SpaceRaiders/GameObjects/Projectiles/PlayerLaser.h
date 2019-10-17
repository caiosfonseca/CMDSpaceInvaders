#pragma once
#include "Laser.h"

class PlayerLaser : public Laser
{
public:

	PlayerLaser();
	PlayerLaser(GameMode* _GM, Vector2D _Pos = Vector2D(), Vector2D _Direction = Vector2D(0.f, -1.f), ObjectType _ObjType = ObjectType::OT_Laser_Player, unsigned char _Sprite = RaiderSprites::RS_PlayerLaser);

	void Update(PlayField& world) override;
	bool CheckBounds(PlayField& world) override;
	bool CheckCollision(PlayField& world) override;
};

