#pragma once
#include <string>
#include <conio.h>
#include "Hero.h"
#include "Level.h"

using namespace std;

class Sett
{
public:
	Sett(string levelFile);

	void PlayGame();
	void PlayerMove();
	void DrawInitWindow();
private:
	Level _level;
	Player _player;
};