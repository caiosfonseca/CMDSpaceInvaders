#include "GameMode.h"
#include "../GameObjects/Ships/PlayerShip.h"
#include "PlayField.h"
#include "../GameObjects/Ships/Alien.h"

GameMode::GameMode(int _NOfAliens, float _PowerUpRate, Vector2D _MapSize, int _DesiredFrameRate, GameState _GS, GameType _GT, int _Seed)
{
	MapSize = _MapSize;
	DesiredFrameRate = _DesiredFrameRate;
	Score = 0;
	GS = _GS;
	GT = _GT;
	Seed = _Seed;
	rGen.seed(Seed);
	PowerUpRate = _PowerUpRate;
	MaxNOfAliens = _NOfAliens;
}

void GameMode::SetPlayerShip(PlayerShip* _PS)
{
	PS = _PS;
}

PlayerShip* GameMode::GetPlayerShip()
{
	return PS;
}


void GameMode::SetPlayField(PlayField* _PF)
{
	PF = _PF;
}

PlayField* GameMode::GetPlayField()
{
	return PF;
}

void GameMode::IncreaseScore(Alien* ET)
{
	switch (ET->ObjType)
	{
	case ObjectType::OT_Alien_Ship:
		Score += ScoreType::ST_Alien_Ship;
		break;
	case ObjectType::OT_Alien_Ship_Better:
		Score += ScoreType::ST_Alien_Ship_Better;
		break;
	default:
		break;
	}
}
