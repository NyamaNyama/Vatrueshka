#include "Level.h"

Level::Level()
{
}

void Level::LoadLevel(string fileName, Player& player)
{
	player.Init(1, 200, 5, 20, 10);
	ifstream file;
	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}
	string line;
	while (getline(file, line))
	{
		_levelData.push_back(line);
	}
	file.close();


	char tile;
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];
			switch (tile)
			{
			case '@':
				if (_levelData[i][j+1] != ' ') {
					player.SetPosition(j, i);
					cout << j << " : " << i;
				}
				break;
			case 'E':
				if (_levelData[i][j + 1] != ' ') {
					_enemies.push_back(Enemy("EnemyDef", tile, 1, 10, 0, 10, 50, 3));
					_enemies.back().SetPosition(j, i);
				}
				break;
			case 'B':
				_enemies.push_back(Enemy("Boss", tile, 100, 2000, 10, 2000, 50000000, 6));
				_enemies.back().SetPosition(j, i);
				break;
			case 'Q':
				_items.push_back(Item("Bomb", tile, 100, DamagePack));
				_items.back().SetPosition(j, i);
				break;
			case 'H':
				_items.push_back(Item("Heal", tile, 10, HealthPack));
				_items.back().SetPosition(j, i);
			case 'P':
				_items.push_back(Item("Potion", tile, 10, AttackPack));
				_items.back().SetPosition(j, i);
			default:
				break;
			}

		}
	}
}

void Level::PrintLevel(Player& player)
{
	system("cls");
	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s", _levelData[i].c_str());
		switch (i)
		{
		case 1:
			printf("\tPlayer stats:");
			break;
		case 2:
			printf("\tHealth: %d", player.GetHealth());
			break;
		case 3:
			printf("\tAttack: %d", player.GetAttack());
			break;
		case 4:
			printf("\tDefence: %d", player.GetDefence());
			break;
		case 5:
			printf("\tLevel: %d", player.GetLevel());
			break;
		case 6:
			printf("\tExperience: %d/250", player.GetExperience());
			break;
		}
		printf("\n");
	}
	printf("\n");
}

char Level::GetTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::SetTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::MovePlayer(char input, Player& player)
{
	int playerX, playerY;
	player.GetPosition(playerX, playerY);
	switch (input)
	{
	case 'w':
	case 'W':
		ProcessPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':
	case 'S':
		ProcessPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':
	case 'A':
		ProcessPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':
	case 'D':
		ProcessPlayerMove(player, playerX + 1, playerY);
		break;
	}

}

void Level::UpdateEnemies(Player& player)
{
	int playerX, playerY;
	player.GetPosition(playerX, playerY);
	int enemyX, enemyY;
	char aiMove;
	for (int i = 0; i < _enemies.size(); i++)
	{
		aiMove = _enemies[i].GetMove(playerX, playerY);
		_enemies[i].GetPosition(enemyX, enemyY);
		switch (aiMove)
		{
		case 'w':
			ProcessEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':
			ProcessEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':
			ProcessEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			ProcessEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

void Level::BattleEnemy(Player& player, int targetX, int targetY)
{
	int enemyX, enemyY, attackRoll, attackResult, playerX, playerY, len;
	string name;
	player.GetPosition(playerX, playerY);
	len = _enemies.size();
	for (int i = 0; i < len; i++)
	{
		_enemies[i].GetPosition(enemyX, enemyY);
		if (targetX == enemyX && targetY == enemyY)
		{
			attackRoll = player.Attack();
			name = _enemies[i].GetName();
			printf("Player attacked %s with a roll of %d\n", name.c_str(), attackRoll);
			attackResult = _enemies[i].TakeDamage(attackRoll);
			if (attackResult != 0)
			{
				printf("%s die!\n", name.c_str());
				player.AddExperience(attackResult);
				SetTile(targetX, targetY, '.');
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				system("pause");
				return;
			}
			attackRoll = _enemies[i].Attack();
			printf("%s attacked player with a roll of %d\n", name.c_str(), attackRoll);
			attackResult = player.TakeDamage(attackRoll);
			if (attackResult != 0)
			{
				printf("You die!\n");
				SetTile(playerX, playerY, 'x');
				system("pause");
				player.EndupDialog();
			}
			system("pause");
			return;
		}
	}
}

void Level::ProcessPlayerMove(Player& player, int targetX, int targetY)
{
	char movingTile;
	int playerX, playerY;
	player.GetPosition(playerX, playerY);
	movingTile = GetTile(targetX, targetY);
	switch (movingTile)
	{
	case '#':
		break;
	case '.':
		player.SetPosition(targetX, targetY);
		SetTile(targetX, targetY, '@');
		SetTile(playerX, playerY, '.');
		break;
	case 'B':
		player.SetPosition(targetX, targetY);
		SetTile(targetX, targetY, '@');
		SetTile(playerX, playerY, '.');
		ProcessItemPicking(player, targetX, targetY);
		break;
	case 'H':
		player.SetPosition(targetX, targetY);
		SetTile(targetX, targetY, '@');
		SetTile(playerX, playerY, '.');
		ProcessItemPicking(player, targetX, targetY);
		break;
	case 'M':
		player.SetPosition(targetX, targetY);
		SetTile(targetX, targetY, '@');
		SetTile(playerX, playerY, '.');
		ProcessItemPicking(player, targetX, targetY);
		break;
	default:
		BattleEnemy(player, targetX, targetY);
		break;
	}
}

void Level::ProcessEnemyMove(Player& player, int enemyIndex, int targetX, int targetY)
{
	char movingTile;
	int enemyX, enemyY;
	_enemies[enemyIndex].GetPosition(enemyX, enemyY);
	movingTile = GetTile(targetX, targetY);
	switch (movingTile)
	{
	case '#':
		break;
	case '.':
		_enemies[enemyIndex].SetPosition(targetX, targetY);
		SetTile(targetX, targetY, _enemies[enemyIndex].GetTile());
		SetTile(enemyX, enemyY, '.');
		break;
	case '@':
		BattleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::ProcessItemPicking(Player& player, int targetX, int targetY) {
	int playerX, playerY, itemX, itemY, boost, damage;
	player.GetPosition(playerX, playerY);
	for (int i = 0; i < _items.size(); i++) {
		_items[i].GetPosition(itemX, itemY);
		if (targetX == itemX && targetY == itemY) {
			ItemType type = _items[i].GetType();
			int value = _items[i].GetValue();
			damage = value - player.GetDefence();
			string name = _items[i].GetName();
			switch (type)
			{
			case DamagePack:
				player.TakeDamage(value);
				printf("Player stepped on %s and received %d damage!\n", name.c_str(), damage);
				if (player.GetHealth() < 0) {
					printf("You die!\n");
					SetTile(playerX, playerY, 'x');
					system("pause");
					player.EndupDialog();
				}
				break;
			case AttackPack:
				player.IncreaseAttack(value);
				printf("Player picked up a %s and received +%d attack boost!\n", name.c_str(), value);
				break;
			case HealthPack:
				player.IncreaseHealth(value);
				printf("Player picked up a %s and received +%d health boost!\n", name.c_str(), value);
				break;
			default:
				break;
			}
			_items[i] = _items.back();
			_items.pop_back();
			system("pause");
			return;
		}
	}
}
