#include "level.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include "curses.h"
#include <Windows.h>

level::level() {

}

void level::load(string fileName, Player& player) {

	//Loads the level
	ifstream file;
	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	file.open("levelsname.txt");
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}


	while (getline(file, line)) {
		_levelName.push_back(line);
	}

	file.close();


	//Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			case 'Z': 
				_enemies.push_back(Enemy("Zombie", tile, 1, 3, 1, 10, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'G': 
				_enemies.push_back(Enemy("Goblin", tile, 2, 30, 5, 15, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': 
				_enemies.push_back(Enemy("Ogr", tile, 4, 20, 40, 20, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': 
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 500000));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}
}


void level::print() {
	clear();
	//cout << string(100, '\n');

	initscr();                 // Инициализация ncurses
	curs_set(0);               // Делаем курсор невидимым
	//printw("Hello, World!");   // Вывод строки Hello, World!
	//refresh();                 // Отображение строки на реальном экране
	//getch();                   // Ожидание пользовательского ввода
	//endwin();
	
	//getPChar(current_health, current_level, current_attack, current_defence, current_exp);
	for (int i = 0; i < _levelData.size(); i++) {
		//printf("%s", _levelData[i].c_str());
		printw(_levelData[i].c_str());
		if (i == 5) { printw("   current hp = %d", current_health); }
		if (i == 6) { printw("   current level = %d", current_level); }
		if (i == 7) { printw("   current attack = %d", current_attack); }
		if (i == 8) { printw("   current defence = %d", current_defence); }
		if (i == 9) { printw("   current exp = %d", current_exp); }
		printw("\n");
		refresh();
		//printf("\n");

	}
	//printf("\n");
}



void level::MovePlayer(char input, Player &player) {
	player.getPlayerChar(current_health, current_level, current_attack, current_defence, current_exp);
	
	int playerX;
	int playerY;
	//cout << _levelName[0];
	//system("PAUSE");
	player.getPosition(playerX, playerY);


	switch (input) {
	case 'w': //up
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's': //down
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a': //left
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd': //right
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		//printf("INVALID INPUT!\n");
		//system("PAUSE");
		break;
	}

}

void level::UpdateEnemies(Player& player) {
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove) {
		case 'w': //up
			processEnemyMove(player, i , enemyX, enemyY - 1);
			break;
		case 's': //down
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a': //left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd': //right
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		default:
			break;
		}
	}
}

char level::getTile(int x, int y) {
	return _levelData[y][x];
}

void level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void level::processPlayerMove(Player& player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case 'B':
		player.addHealth(20);
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		player.getPlayerChar(current_health, current_level, current_attack, current_defence, current_exp);
		break;
	case '/':
		_levelData.clear();
		_enemies.clear();
		//load("level2.txt", player);
		load(_levelName[++lvl], player);
		break;
	case '$':
		_levelData.clear();
		_enemies.clear();
		load(_levelName[--lvl], player);
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void level::processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	
	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void level::battleMonster(Player& player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	

	int enemyX;
	int enemyY;
	int attackRoll;
	int attackResult;
	string enemyName;

	for (int i = 0; i < _enemies.size(); i++) {

		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();

		if (targetX == enemyX && targetY == enemyY) {

			//Battle!
			attackRoll = player.attack();
			printw("Player attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
			refresh();
			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printw("Monster died!\n");

				//Remove the enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				//system("PAUSE");
				player.addExperience(attackResult);
				refresh();

				return;
			}

			//Monster turn!
			attackRoll = _enemies[i].attack();
			printw("%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);
			refresh();
			attackResult = player.takeDamage(attackRoll);
			//system("PAUSE");

			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print();
				printw("You died!\n");
				refresh();
				//system("PAUSE");

				exit(0);
			}
			return;
		}
	}

}