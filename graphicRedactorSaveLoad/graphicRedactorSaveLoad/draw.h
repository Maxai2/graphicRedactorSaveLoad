#pragma once

#include <iostream>
//#include <conio.h>
#include <Windows.h>

using namespace std;

enum Colors
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	BROWN,
	LIGHTGREY,
	GREY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE
};
//-----------------------------------------------------------------------------------------------
#pragma pack(1)
typedef struct
{
	char symbol;
	//Colors bg;
	//Colors fg;
	char bg : 4;
	char fg : 4;
}
CELL;
#pragma pack(4)
//-----------------------------------------------
const int row = 20, col = 50;
const int rowS = 7, colS = 18;

enum Command
{
	cNew, cColors, cSymbols, cLoad, cSave, cClear, cExit, cDraw
};

Command menu(bool first, int &sel);
void showMenu(bool first, int sel);
void ShowSymCol();
void clearMenu();
void symbols();
char cSymbol();
int cColorfg();
int cColorbg();
void draw(char sym = '*', int fg = LIGHTGREY, int bg = BLACK);
void clearColorRedact();
void clearTable();
void Cursor(bool showFlag);
void frame();
bool save(char *FileName);
bool load(char *FileName);
char * AskFileName(char *Prompt);

//HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//-----------------------------------------------------------------------------------------------
#define COLOR(foreground, background) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background * 16 + foreground)
#define COORDS(row, col) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)col, (short)row })
#define RAND(min, max) rand() % (max - min + 1) + min
//-----------------------------------------------------------------------------------------------
template <typename T> void drawData(T data, Colors c1, Colors c2, int row = -1, int col = -1)
{
	COLOR(c1, c2);
	if (row >= 0 && col >= 0)
	{
		COORDS(row, col);
	}
	cout << data;
	COLOR(LIGHTGREY, BLACK);
}
//-----------------------------------------------------------------------------------------------
//void draw(int row, int col, int height, int width, Colors c)
//{
//	COLOR(c, c);
//	for (size_t i = row; i < row + height; i++)
//	{
//		for (size_t j = col; j < col + width; j++)
//		{
//			COORDS(i, j);
//			cout << ' ';
//		}
//	}
//	COLOR(LIGHTGREY, BLACK);
//}
//----------------------------------------------------------------------------------------------
