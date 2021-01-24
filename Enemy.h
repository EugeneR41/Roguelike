#pragma once
#include <string>

using namespace std;

class Enemy {
public:
	Enemy(string name, char tile, int level, int attack, int defence, int health, int exp);

	void setPosition(int x, int y);

	void getPosition(int& x, int& y);

	int attack();
	int takeDamage(int attack);
	string getName() {return _name;}
	char getTile() {return _tile;}

	char getMove(int playerX, int playerY);

private:
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defence;
	int _health;
	int _experienceValue;

	int _x;
	int _y;
};

