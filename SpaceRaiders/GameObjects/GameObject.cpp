#include "GameObject.h"
#include "../Game/PlayField.h"

GameObject::GameObject()
{
	GM = nullptr;  
	ObjType = ObjectType::OT_Empty;
	Pos = Vector2D();
	Sprite = RaiderSprites::RS_BackgroundTile;
}

GameObject::GameObject(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite)
{
	GM = _GM;
	ObjType = _ObjType;
	Pos = _Pos;
	Sprite = _Sprite;
}

GameObject::~GameObject()
{
}

void GameObject::SetHealth(float _Health)
{
	Health = _Health;
}

float GameObject::GetHealth()
{
	return Health;
}

void GameObject::Update(PlayField& world)
{
}

bool GameObject::DecreaseHealth(PlayField& world)
{
	return true;
}
