#include <iostream>
#include <time.h>
#include <windows.h>
//-----------------------------------------------
#include "draw.h"

using namespace std;

typedef struct 
{
	char symbol;
	Colors bg;
	Colors fg;
}Cell;
//-----------------------------------------------
void main()
{
	srand(time(NULL));
	Cell field[19][49] = {};

	menu(field);

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 30; j++)
	//	{
	//		field[i][j].symbol = rand() % 230 + 15;
	//		field[i][j].bg = Colors(rand() % 16);
	//		field[i][j].fg = Colors(rand() % 16);
	//	}
	//}

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 30; j++)
	//	{
	//		drawData(field[i][j].symbol, field[i][j].fg, field[i][j].bg);
	//	}
	//	cout << endl;
	//}
}