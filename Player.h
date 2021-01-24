#pragma once

class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();
	int takeDamage(int attack);

	void setPosition(int x, int y);

	void addExperience(int experience);

	void addHealth(int health);


	void getPosition(int& x, int& y);

	void getPlayerChar(int& health, int& level, int& attack, int& defence, int& exp);

private:
	int _level;
	int _health;
	int _defaultHealth;
	int _attack;
	int _defence;
	int _experience;

	int _x;
	int _y;
};
