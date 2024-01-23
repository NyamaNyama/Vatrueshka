#include "Item.h"
#include <string>

Item::Item(std::string name, char tile, int value, ItemType type) : _name(name), _tile(tile), _value(value), _type(type) {}

Item::~Item() = default;

string Item::GetName() const {
	return _name;
}

void Item::SetName(string name) {
	_name = name;
}

char Item::GetTile() const {
	return _tile;
}

void Item::SetTile(char tile) {
	_tile = tile;
}

int Item::GetValue() const {
	return _value;
}

void Item::SetValue(int value) {
	_value = value;
}

ItemType Item::GetType() const {
	return _type;
}

void Item::SetType(ItemType type) {
	_type = type;
}

void Item::GetPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

void Item::SetPosition(int x, int y) {
	_x = x;
	_y = y;
}


