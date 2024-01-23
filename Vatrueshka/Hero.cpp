#include "Hero.h"

Player::Player()
{
	_x = 0; _y = 0;
}

void Player::Init(int level, int health, int attack, int defence, int experience)
{
	_level = level; _health = health;
	_attack = attack; _defence = defence;
	_experience = experience;
}

void Player::SetPosition(int x, int y)
{
	_x = x; _y = y;
}

void Player::GetPosition(int& x, int& y)
{
	x = _x;
	y = _y;
}

int Player::Attack()
{
	static default_random_engine randEng(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);
	return attackRoll(randEng);
}

void Player::AddExperience(int experience)
{
	_experience += experience;
	while (_experience >= 250)
	{
		printf("Level up!\n");
		_experience -= 50;
		_attack += 2;
		_defence += 1;
		_health += 10;
		_level++;
	}
}

int Player::TakeDamage(int damage)
{
	damage = damage - _defence;
	if (damage > 0)
	{
		_health = _health - damage;
		if (_health <= 0)
			return 1;
	}
	return 0;
}

int Player::IncreaseAttack(int attack) {
	_attack += attack;
	return attack;
}

int Player::IncreaseHealth(int health) {
	_health += health;
	return health;
}
