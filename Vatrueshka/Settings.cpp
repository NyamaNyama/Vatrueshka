#include "Settings.h"
#include <curses.h>

void Sett::DrawInitWindow() {
	initscr();
	noecho();
	int highScore = 0;
	int ch;
	
    mvprintw(LINES/2 - 5, (COLS-strlen("*****************"))/2, "*****************");
    mvprintw(LINES/2 - 4, (COLS-strlen("**** VATRUESHKA ***"))/2, "**** VATRUESHKA ***");
    mvprintw(LINES/2 - 3, (COLS-strlen("*****************"))/2, "*****************");
	mvprintw(LINES / 2 + 2, (COLS - strlen("Press space to continue...")) / 2, "Press space to continue....");

	while ((ch = getch()) != ' ') {}
	clear();

	mvprintw(1, (COLS - strlen("*****************")) / 2, "*****************");
	mvprintw(2, (COLS - strlen("**** VATRUESHKA ***")) / 2, "**** VATRUESHKA ***");
	mvprintw(3, (COLS - strlen("*****************")) / 2, "*****************");
	mvprintw(5, (COLS - strlen("**** MENU ****")) / 2, "**** MENU ****");
	mvprintw(LINES / 2, (COLS - strlen("Press SPACE to start")) / 2, "Press SPACE to start");
	mvprintw(LINES - 2, (COLS - strlen("Player's high score: ")) / 2, "Player's high score: "); 

	while ((ch = getch()) != ' ') {}
	clear();
	endwin();
}

Sett::Sett(string levelFile)
{
	DrawInitWindow();
	_player.StartupDialog();
	_level.LoadLevel(levelFile, _player);
	_level.PrintLevel(_player);

}

void Sett::PlayGame()
{
	bool isDone = false;
	while (isDone != true)
	{
		_level.PrintLevel(_player);
		PlayerMove();
		_level.UpdateEnemies(_player);
	}
}

void Sett::PlayerMove()
{
	char input;
	printf("Enter a move command (w/a/s/d):\n");
	input = _getch();
	_level.MovePlayer(input, _player);
}