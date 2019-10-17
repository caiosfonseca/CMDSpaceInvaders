#include <vector>
#include <sstream>
#include <iostream>
#include <Windows.h>

#include "Renderer.h"
#include "../GameObjects/Ships/PlayerShip.h"
#include "GameMode.h"
#include "PlayField.h"

using namespace std;

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

Renderer::Renderer(const Vector2D& Bounds, GameMode* _GM)
: renderBounds(Bounds)
{
	canvasSize = (int)(Bounds.x * Bounds.y);
	disp[0].canvas = new unsigned char[canvasSize];
	disp[1].canvas = new unsigned char[canvasSize];
	GM = _GM;
}


Renderer::~Renderer()
{
	delete[] disp[0].canvas;
	delete[] disp[1].canvas;
}

void Renderer::Update(const RenderItemList& RenderList)
{
	FillCanvas(RS_BackgroundTile);
	
	for (auto ri : RenderList)
	{
		// std::cout << "object drawn" << std::endl;
		int x = int(ri.Pos.x);
		int y = int(ri.Pos.y);

		if (x >= 0 && x < renderBounds.x && y >= 0 && y < renderBounds.y)
		{
			*CurCanvas((int)ri.Pos.x, + (int)ri.Pos.y) = ri.Sprite;
		}
	}
	
	DrawCanvas();
}

unsigned char* Renderer::CurCanvas(int x, int y)
{
	return &disp[curIdx % 2].canvas[x + (int)renderBounds.x * y];
}

void Renderer::FillCanvas(unsigned char Sprite)
{
	for (int i = 0; i < canvasSize; i++)
	{
		*CurCanvas(i,0) = Sprite;
	}
}

void Renderer::DrawCanvas()
{
	for (int y = 0; y < renderBounds.y; y++)
	{
		for (int x = 0; x < renderBounds.x; x++)
		{
			setCursorPosition(x, y);
			cout << *CurCanvas(x,y);
		}
		cout << std::endl;
	}
	string AliensCount = "";
	stringstream ssm;
	if (GM->GT != GameType::GT_Endless)
	{
		int MaxAliens = GM->GT == GameType::GT_Waves ? GM->GetPlayField()->LastAlienWaveSize : GM->MaxNOfAliens;
		ssm << "Aliens Alive: " << GM->GetPlayField()->NOfAliensAlive << " / " << MaxAliens << Padding;
		AliensCount = ssm.str();
	}

	string WaveText = "";
	if (GM->GT == GameType::GT_Waves)
	{
		ssm = stringstream();
		ssm << "Wave: " << GM->CurrentWave << Padding;
		WaveText = ssm.str();
	}


	cout << "Seed: " << GM->Seed << Padding << WaveText << "Score: " << GM->Score << Padding << AliensCount << "Active Powers: " << GM->GetPlayerShip()->GetActivePowers().c_str() << endl;
	curIdx++;
}

