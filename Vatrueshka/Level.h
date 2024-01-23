#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "Hero.h"
#include "Enemy.h"
#include "Item.h"

using namespace std;

class Level
{
public:
	Level();
	void LoadLevel(string fileName, Player& player);
	void PrintLevel(Player& player);

	void MovePlayer(char input, Player& player);

	void UpdateEnemies(Player& player);

	char GetTile(int x, int y);
	void SetTile(int x, int y, char tile);
private:
	void ProcessPlayerMove(Player& player, int targetX, int targetY);
	void ProcessEnemyMove(Player& player, int enemyIndex, int targetX, int targetY);
	void BattleEnemy(Player& player, int targetX, int targetY);
	void ProcessItemPicking(Player& player, int targetX, int targetY);

	vector<string> _levelData;
	vector<Enemy> _enemies;
	vector<Item> _items;
};

