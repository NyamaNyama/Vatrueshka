#pragma once
#include <string>

using namespace std;

enum ItemType { DamagePack, AttackPack, HealthPack };
class Item {
public:
	Item(std::string name, char tile, int value, ItemType type);
	virtual ~Item();
	std::string GetName() const;
	void SetName(std::string name);
	char GetTile() const;
	void SetTile(char tile);
	int GetValue() const;
	void SetValue(int value);
	ItemType GetType() const;
	void SetType(ItemType type);
	void GetPosition(int& x, int& y);
	void SetPosition(int x, int y);

protected:
	std::string _name;
	char _tile;
	int _value;
	ItemType _type;
	int _x;
	int _y;
};