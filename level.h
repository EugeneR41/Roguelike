#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
//#include "curses.h";

using namespace std;

class level
{
public:
	level();

	void load(string fileName, Player &player);
	void print();

	void MovePlayer(char input, Player& player);
	void UpdateEnemies(Player& player);

	char getTile(int x, int y);

	void setTile(int x, int y, char tile);


private:
	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY);
	void battleMonster(Player& player, int targetX, int targetY);

private:
	vector <string> _levelData;
	vector <string> _levelName;
	vector <Enemy> _enemies;
	int lvl = 0;
	int current_health;
	int current_level;
	int current_attack;
	int current_defence;
	int current_exp;
};

