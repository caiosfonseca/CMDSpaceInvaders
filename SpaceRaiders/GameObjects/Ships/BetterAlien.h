#pragma once
#include "Alien.h"
class BetterAlien :	public Alien
{
public:

	BetterAlien();
	BetterAlien(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Alien_Ship_Better, unsigned char _Sprite = RaiderSprites::RS_BetterAlien);
	BetterAlien(float _direction, GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Alien_Ship_Better, unsigned char _Sprite = RaiderSprites::RS_BetterAlien);

	void Update(PlayField& world) override;
	bool DecreaseHealth(PlayField& world) override;
};

