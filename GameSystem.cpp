#include "GameSystem.h"
#include <iostream>
#include <conio.h>
#include "curses.h"
#include <windows.h>
#include <chrono>
#include <thread>
#include <utility>
#include <time.h> 


GameSystem::GameSystem(string levelFileName) {

    const int width = 100;
    const int height = 25;

    initscr();
    curs_set(0);
    refresh();

    int offsetx = (COLS - width) / 2;
    int offsety = (LINES - height) / 2;

    WINDOW* win = newwin(height, width, offsety, offsetx);

    char hello[] = "HOW TO PLAY:";
    char h1[] = "Movement :";
    char h2[] = "W - move up";
    char h3[] = "S - move down";
    char h4[] = "A - move left";
    char h5[] = "D - move right";

    char l1[] = "Rules :";
    char l2[] = "@ - is a player";
    char l3[] = "M - the enemies";
    char l4[] = "# - the wall";
    char l5[] = "B - heal point(+20)";
    char l6[] = "/ -next level";

    char cont[] = "PRESS ANY KEY TO CONTINUE";

    mvaddstr(LINES / 6, (COLS - strlen(hello)) / 2, hello);
    mvaddstr(LINES / 4, (COLS - strlen(h1)) / 7, h1);
    mvaddstr(LINES / 3.3, (COLS - strlen(h1)) / 7, h2);
    mvaddstr(LINES / 2.8, (COLS - strlen(h1)) / 7, h3);
    mvaddstr(LINES / 2.6, (COLS - strlen(h1)) / 7, h4);
    mvaddstr(LINES / 2.5, (COLS - strlen(h1)) / 7, h5);

    mvaddstr(LINES / 4, (COLS - strlen(l1)) / 1.35, l1);
    mvaddstr(LINES / 3.3, (COLS - strlen(l1)) / 1.35, l2);
    mvaddstr(LINES / 2.8, (COLS - strlen(l1)) / 1.35, l3);
    mvaddstr(LINES / 2.6, (COLS - strlen(l1)) / 1.35, l4);
    mvaddstr(LINES / 2.5, (COLS - strlen(l1)) / 1.35, l5);
    mvaddstr(LINES / 2.3, (COLS - strlen(l1)) / 1.35, l6);

    mvaddstr(LINES / 1.4, (COLS - strlen(cont)) / 2, cont);
    box(win, 0, 0);

    wrefresh(win);
    getch();

    delwin(win);
   // endwin();
	_player.init(1, 100, 10, 10, 0);
	_level.load(levelFileName, _player);
	//system("PAUSE");
}

void GameSystem::playGame() {

	bool isDone = false;
 
	while(isDone != true) {
        

        playerMove();
		_level.print();
       // Sleep(200);
		_level.UpdateEnemies(_player);
    }

}

void GameSystem::playerMove() {
    char input = 'r';
    
    //if (_kbhit() != 0)
    //{
        input = _getch();
    //}
	
	_level.MovePlayer(input, _player);
}