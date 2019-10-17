#pragma once

#include "../Game/GameMode.h"
#include "../Game/Renderer.h"
#include "../Utils/Vector2D.h"

class PlayField;

enum ObjectType {
	OT_Empty,
	OT_Explosion,
	OT_Laser_Alien,
	OT_Laser_Player,
	OT_Alien_Ship,
	OT_Alien_Ship_Better,
	OT_Player_Ship,
	OT_BlockingWall,
	OT_PowerUp
};

enum ScoreType {
	ST_Alien_Ship = 10,
	ST_Alien_Ship_Better = 20
};

class GameObject
{
public:
	GameMode* GM;
	ObjectType ObjType;
	Vector2D Pos;
	unsigned char Sprite;

	GameObject();
	GameObject(GameMode* _GM, Vector2D _Pos = Vector2D(), ObjectType _ObjType = ObjectType::OT_Empty, unsigned char _Sprite = RaiderSprites::RS_BackgroundTile);
	~GameObject();

	void SetHealth(float _Health);
	float GetHealth();

	virtual void Update(PlayField& world);
	virtual bool DecreaseHealth(PlayField& world);

private:
	float Health = 1.f;
};

