// SpaceRaiders.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <memory>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "Utils/Vector2D.h"
#include "Game/GameMode.h"
#include "Game/Playfield.h"
#include "Game/Renderer.h"
#include "Controllers/RndInput.h"
#include "Controllers/InputController.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/FX/Explosion.h"
#include "GameObjects/Projectiles/AlienLaser.h"
#include "GameObjects/Projectiles/PlayerLaser.h"
#include "GameObjects/Ships/Alien.h"
#include "GameObjects/Ships/PlayerShip.h"


using namespace std;

string Logo[] =
{
	"                                                ",
	"        _________                                     ",
	"       /   _____/__________    ____  ____             ",
	"       \\_____  \\\\____ \\__  \\ _/ ___\\/ __ \\      ",
	"       /        \\  |_> > __ \\\\  \\__\\  ___/            ",
	"      /_______  /   __(____  /\\___  >___  >           ",
	"              \\/|__|       \\/     \\/    \\/            ",
	"__________        .__    .___                   ",
	"\\______   \\_____  |__| __| _/___________  ______",
	" |       _/\\__  \\ |  |/ __ |/ __ \\_  __ \\/  ___/",
	" |    |   \\ / __ \\|  / /_/ \\  ___/|  | \\/\\___ \\ ",
	" |____|_  /(____  /__\\____ |\\___  >__|  /____  >",
	"        \\/      \\/        \\/    \\/           \\/ ",
	"                                                "
};

string Menu[] =
{
	"                                                       ",
	"           Press S to start a new Random Round         ",
	"            Press E to play an Endless Round           ",
	"             Press W to play a Waves Round             ",
	"              Press A to let the AI play               ",
	"              Press any other key to quit              "
};

char ReadChar(string message)
{
	string input = "";
	while (true) {
		cout << message.c_str();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();
		getline(cin, input);

		if (input.length() == 1) {
			return input[0];
			break;
		}

		cout << "Invalid character, please try again" << endl;
	}
}

int ReadInt(string message)
{
	string input;
	int myNumber;
	while (true) {
		cout << "Please enter a valid number: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.clear();
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> myNumber)
		{
			return myNumber;
		}
		cout << "Invalid number, please try again" << endl;
	}
}

int GenerateNewSeed()
{
	srand((unsigned int)time(0));
	return (rand() % 10000) + 1;
}

int AskForSeed()
{
	char answer = ' ';
	int r = GenerateNewSeed();

	int chosenSeed = -1;
	answer = ReadChar("Do you want to choose a seed? Y/N\n");
	answer = toupper(answer);
	if (answer == 'Y')
	{
		chosenSeed = ReadInt("Type a seed number:");
	}
	else
	{
		chosenSeed = r;
	}
	cout << "Chosen seed " << chosenSeed << endl;
	return chosenSeed;
}

bool MainMenu(int& ChosenSeed, GameState& ChosenGS, GameType& ChosenGT)
{
	char answer = ' ';
	string padding = "     ";
	for (string line : Logo)
	{
		cout << padding.c_str() << line.c_str() << "\n";
	}
	for (string line : Menu)
	{
		cout << line.c_str() << "\n";
	}
	answer = ReadChar("\n");
	answer = toupper(answer);
	system("cls");

	ChosenSeed = AskForSeed();
	ChosenGT = GameType::GT_Default;
	ChosenGS = GameState::GS_Playing;
	if (answer == PressedKeys::PK_NewGame)
	{
	}
	else if (answer == PressedKeys::PK_EndlessRound)
	{
		ChosenGT = GameType::GT_Endless;
	}
	else if (answer == PressedKeys::PK_AI)
	{
		ChosenGS = GameState::GS_PlayingAI;
	}
	else if (answer == PressedKeys::PK_WavesRound)
	{
		ChosenGT = GameType::GT_Waves;
	}
	else
	{
		ChosenSeed = -1;
		return false;
	}
	return true;
}

void StartGame(GameMode* GM, Renderer* mainRenderer, PlayField* world, GameState ChosenGS)
{
	
	world->SetGameMode(GM);
	GM->SetPlayField(world);

	// Populate aliens
	if (GM->GT != GameType::GT_Endless)
	{
		world->SpawnAlienWave();
	}
	
	// Add player
	PlayerShip* p = new PlayerShip(GM, Vector2D(GM->MapSize.x / 2, GM->MapSize.y - 1));
	world->SetPlayerObject(p);
	world->AddObjectToAddQueue(p);

	GM->SetPlayerShip(p);

	if (ChosenGS == GameState::GS_PlayingAI)
	{
		world->ControllerInput = new RndInput(GM);
	}
	else
	{
		world->ControllerInput = new InputController(GM);
	}
}


int main()
{
	float PowerUpRate = 0.65f;
	Vector2D WorldSize = Vector2D(80.f, 28.f);
	int DesiredFrameRate = 60;
	int NOfAliens = 25;
	while (true)
	{
		GameState ChosenGS = GameState::GS_MainMenu;
		GameType ChosenGT = GameType::GT_Default;
		int ChosenSeed = -1;
		
		if (!MainMenu(ChosenSeed, ChosenGS, ChosenGT))
		{
			return 0;
		}

		GameMode* GM = new GameMode(NOfAliens, PowerUpRate, WorldSize, DesiredFrameRate, ChosenGS, ChosenGT, ChosenSeed);
		Renderer* mainRenderer = new Renderer(GM->MapSize, GM);
		PlayField* world = new PlayField(GM->MapSize);
		StartGame(GM, mainRenderer, world, ChosenGS);

		char response = ' ';
		int sleepTime = 1000 / GM->DesiredFrameRate;
		while (GM->GS != GameState::GS_MainMenu)
		{
			while (GM->GS != GameState::GS_GameOver) // break when game-over
			{
				world->Update();

				RenderItemList rl;
				for (auto it : world->GetGameObjects())
				{
					RenderItem a = RenderItem(it->Pos, it->Sprite);
					rl.push_back(a);
				}

				mainRenderer->Update(rl);

				// Sleep a bit so updates don't run too fast
				this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
			}
			cout << "Game Over!" << endl;
			response = ReadChar("Press R to play again, M to go to the main menu and any other key to quit\n");
			response = toupper(response);
			system("cls");
			if (response == PressedKeys::PK_Restart)
			{
				GM->GS = ChosenGS;
				GM = new GameMode(NOfAliens, PowerUpRate, WorldSize, DesiredFrameRate, ChosenGS, ChosenGT, ChosenSeed);
				mainRenderer = new Renderer(GM->MapSize, GM);
				world = new PlayField(GM->MapSize);
				StartGame(GM, mainRenderer, world, ChosenGS);
			}
			else if (response == PressedKeys::PK_MainMenu){
				GM->GS = GameState::GS_MainMenu;
				break;
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

