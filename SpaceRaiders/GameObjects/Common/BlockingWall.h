#pragma once
#include "../GameObject.h"

class BlockingWall : public GameObject
{
public:
	BlockingWall();
	BlockingWall(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_BlockingWall, unsigned char _Sprite = RaiderSprites::RS_BlockingWalls);

	virtual bool DecreaseHealth(PlayField& world) override;

};

