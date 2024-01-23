#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "Settings.h"

using namespace std;

int main()
{
	Sett start("MapDraw.txt");
	start.PlayGame();
	return 0;
}