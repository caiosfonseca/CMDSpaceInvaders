#include "Explosion.h"
#include "../../Game/PlayField.h"

Explosion::Explosion() : GameObject()
{
}

Explosion::Explosion(GameMode* _GM, Vector2D _Pos, ObjectType _ObjType, unsigned char _Sprite) : GameObject(_GM, _Pos, _ObjType, _Sprite)
{
}

void Explosion::Update(PlayField& world)
{
	timer--;
	if (!timer)
	{
		world.AddObjectToRemoveQueue(this);
		delete this;
	}
}