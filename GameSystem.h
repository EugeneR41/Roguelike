#pragma once
#include "Player.h"
#include "level.h"
#include <string>

using namespace std;

class GameSystem
{
public:
	GameSystem(string levelFileName);

	void playGame();
	void playerMove();

private:
	level _level;
	Player _player;
};
