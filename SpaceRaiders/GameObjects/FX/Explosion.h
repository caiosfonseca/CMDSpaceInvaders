#pragma once
#include "../GameObject.h"

class Explosion : public GameObject
{
public:
	// Explosion lasts 5 ticks before it dissappears
	int timer = 5;
	Explosion();
	Explosion(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Explosion, unsigned char _Sprite = RaiderSprites::RS_Explosion);

	void Update(PlayField& world);
};
