#pragma once
#include <random>
#include "../Utils/Vector2D.h"

typedef std::uniform_int_distribution<int> intRand;
typedef std::uniform_real_distribution<float> floatRand;
class PlayerShip;
class PlayField;
class Alien;

enum GameState {
	GS_MainMenu,
	GS_Playing,
	GS_PlayingAI,
	GS_WaveFinished,
	GS_GameOver
};

enum GameType
{
	GT_Endless,
	GT_Waves,
	GT_Default
};

enum PressedKeys {
	PK_Restart = 'R',
	PK_NewGame = 'S',
	PK_EndlessRound = 'E',
	PK_WavesRound = 'W',
	PK_AI = 'A',
	PK_MainMenu = 'M',
	PK_Quit = 'Q'
};

class GameMode
{

public:
	std::default_random_engine rGen;
	int Seed = 1;
	Vector2D MapSize;
	int DesiredFrameRate = 60;
	int Score = 0;
	float PowerUpRate = 0.65f;
	int MaxNOfAliens = 25;
	int CurrentWave = 0;
	GameState GS = GameState::GS_MainMenu;
	GameType GT = GameType::GT_Default;

	GameMode(int _NOfAliens = 25, float _PowerUpRate = 0.65f, Vector2D _MapSize = Vector2D(80.f, 39.f), int _DesiredFrameRate = 60, GameState _GS = GameState::GS_MainMenu, GameType _GT = GameType::GT_Default, int _Seed = 0);

	void SetPlayerShip(PlayerShip* _PS);
	PlayerShip* GetPlayerShip();

	void SetPlayField(PlayField* _PF);
	PlayField* GetPlayField();

	void IncreaseScore(Alien* ET);

private:
	PlayerShip* PS = nullptr;
	PlayField* PF = nullptr;
};

