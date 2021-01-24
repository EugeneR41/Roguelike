#include "Player.h"
#include <random>
#include <ctime>
#include "curses.h"

using namespace std;

Player::Player() {
	_x = 0;
	_y = 0;
}

//Initializes the palyer
void Player::init(int level, int health, int attack, int defence, int experience) {
	_level = level;
	_health = health;
	_defaultHealth = health;
	_attack = attack;
	_defence = defence;
	_experience = experience;
}

int Player::attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

void Player::addExperience(int experience) {
	_experience += experience;
	int mnojitel;
	//Level up
	if (_experience / 80){
		mnojitel = _experience / 50;
		//printf("Leveled up! your level is %d\n",_level);
		printw("Leveled up! your level is %d\n", _level + 1);
		_experience -= 50 * mnojitel;
		_attack += 10 * mnojitel;
		_defence += 5 * mnojitel;
		_defaultHealth += 10 * mnojitel;
		_health = _defaultHealth;
		_level += 1*mnojitel;
	}
}


void Player::addHealth(int health) {
	if (_health + health > _defaultHealth) {
		_health = _defaultHealth;
	} else {
		_health += health;
	}
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}


void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

void Player::getPlayerChar(int &health, int &level, int &attack, int &defence, int &exp) {
	health = _health;
	level = _level;
	attack = _attack;
	defence = _defence;
	exp = _experience;
}

int Player::takeDamage(int attack) {
	attack -= _defence;
	if (attack > 0) {
		_health -= attack;
		if (_health <= 0) {
			return 1;
		}
	}
	return 0;
}