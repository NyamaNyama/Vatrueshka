#pragma once
#ifndef ROGUE_LIKE_HP_H
#define ROGUE_LIKE_HP_H
class hp {
private:
	unsigned int _CurrentHP;
	unsigned int _MaxHp;
public:
	hp();
	hp(unsigned int maxHP);
	unsigned int GetCurrentHP();
	unsigned int GetMaxtHP();
	void Heal(unsigned int healing);
	void Damage(unsigned int damage);
};
#endif