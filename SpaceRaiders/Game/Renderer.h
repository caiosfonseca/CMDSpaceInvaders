#pragma once

#include <vector>
#include "../Utils/Vector2D.h"

class GameMode;

struct RenderItem
{
	RenderItem(const Vector2D& iPos, char iSprite) : Pos(iPos), Sprite(iSprite) {};
	Vector2D Pos;
	char Sprite;
};
typedef std::vector<RenderItem> RenderItemList;

enum RaiderSprites
{
	RS_BackgroundTile = 0xB0,
	RS_Player = 'P',
	RS_Alien = 'A',
	RS_BetterAlien = 'B',
	RS_BlockingWalls = '#',
	RS_PlayerLaser = 0xBA,
	RS_AlienLaser = '|',
	RS_Explosion = '*',
	RS_SpeedBoost = 'S',
	RS_FireRateBoost = 'F',
	RS_TripleFire = 'T',
};

class Renderer
{
public:
	Renderer(const Vector2D& Bounds, GameMode* _GM);
	~Renderer();
	GameMode* GM;

	// Draws all game objects after clearing filling the Canvas with _ symbol
	void Update(const RenderItemList& RenderList);

private:
	Vector2D renderBounds;
	int curIdx = 0;
	std::string Padding = "   ";

	struct
	{
		unsigned char* canvas = nullptr;
	} disp[2]; // double buffer our canvas for no flicker display

	int canvasSize = 0;
	unsigned char* CurCanvas(int x, int y);

	// Fills whole canvas array with sprite
	void FillCanvas(unsigned char Sprite);

	// Prints canvas char array on console
	void DrawCanvas();
};

