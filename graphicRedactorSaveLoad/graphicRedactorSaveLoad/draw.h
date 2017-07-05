#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

//-----------------------------------------------------------------------------------------------
void menu();
//-----------------------------------------------------------------------------------------------
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
void draw(int row, int col, int height, int width, Colors c)
{
	COLOR(c, c);
	for (size_t i = row; i < row + height; i++)
	{
		for (size_t j = col; j < col + width; j++)
		{
			COORDS(i, j);
			cout << ' ';
		}
	}
	COLOR(LIGHTGREY, BLACK);
}
//-----------------------------------------------------------------------------------------------
void frame()
{
	short rowS = 7, rowF = 26, colS = 18, colF = 67;

	for (short i = rowS; i < rowF; i++)
	{
		COORDS(i, colS);

		for (short j = colS; j < colF; j++)
		{
			if (i == rowS || i == rowF - 1)
				cout << char(178);
			else if (rowS + 1 <= i && i <= rowF - 2 && (j == colS || j == colF - 1))
			{
				COORDS(i, j);
				cout << char(178);
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------
void colors()
{
	COORDS(0, 20);
	cout << "Colors: ";
	for (int i = 1; i < 16; i++)
	{
		COLOR(i, BLACK);
		cout << i << " ";
	}
}
//-----------------------------------------------------------------------------------------------
void symbols()
{
	short row = 9;
	COORDS(row, 0);
	cout << "Symbols:";
	row++;
	for (int i = 34; i <= 126; i++)
	{
		if (i == 34 || i == 36 || 40 <= i && i <= 43 || 45 <= i && i <= 47)
		{
			COORDS(row, 2);
			cout << char(i) << endl;
			row++;
		}
		else if (i == 60 || i == 62 || i == 64 || i == 92 || i == 94 || i == 95 || i == 124 || i == 126)
		{
			COORDS(row, 2);
			cout << char(i) << endl;
			row++;
		}
	}
}
//-----------------------------------------------------------------------------------------------
int cColor()
{
	COORDS(1, 20);
	int col;

	for (int i = 20; i < 46; i++)
		cout << " ";

	COORDS(1, 20);
	COLOR(LIGHTGREY, BLACK);
	cout << "Input number of color: ";
	cin >> col;

	return col;
}
//-----------------------------------------------------------------------------------------------
char cSymbol()
{
	int key, sel = 0;
	short row = 5;
	int sym[17] = { 34, 36, 40, 41, 42, 43, 45, 46, 47, 60, 62, 64, 92, 94, 95, 124, 126 };

	while (true)
	{
		symbols();

		COORDS(row, 2);

		if (sym[sel] % 2 == 0)
		{
			COLOR(4, BLACK);
			cout << char(sym[sel]);
		}

		COORDS(row, 2);

		COLOR(LIGHTGREY, BLACK);
		if (sym[sel] % 2 == 1)
		{
			COLOR(4, BLACK);
			cout << char(sym[sel]);
		}
		COLOR(LIGHTGREY, BLACK);

		key = getch();
		if (key == 0)
			key = getch();

		if (key == 72 && row >= 6) // Up
		{
			sel--;
			row--;
		}
		else if (key == 80 && row <= 20) // Down
		{
			sel++;
			row++;
		}
		else if (key == 13)
			return sym[sel];
	}
}
//-----------------------------------------------------------------------------------------------
void clearMenu()
{
	short rowS = 0, rowF = 5, colS = 0, colF = 15;

	for (short i = rowS; i < rowF; i++)
	{
		for (short j = colS; j < colF; j++)
		{
			COORDS(i, j);

			cout << " ";
		}
	}
}
//-----------------------------------------------------------------------------------------------
void newPicture()
{
	frame();
	symbols();
	colors();

}
//-----------------------------------------------------------------------------------------------
void draw(char symbol, Cell *c)
{
	int key = 0;
	short row = 8, col = 19;
	while (true)
	{
		COORDS(row, col);

		key = getch();
		if (key == 224)
			key = getch();

		if (key == 72 && row > 8) // Up
			row--;
		else if (key == 80 && row < 24) // Down
			row++;
		else if (key == 75 && col > 19) // Left
			col--;
		else if (key == 77 && col < 65) // Right
			col++;
		else if (key == 32) // enter 13 space 32
		{
			COLOR(c.)
			SetConsoleTextAttribute(h, color);
			//putch(cSymbol());
			cout << char(symbol);
		}
		else if (key == 83) // backspace 8 del 83
			cout << " ";
		else if (key == 9)
			menu();
	}
}
//-----------------------------------------------------------------------------------------------
void showMenu(int choose, int sel)
{
	clearMenu();

	if (choose == 1)
	{
		COORDS(0, 0);
		COLOR(sel == 0 ? GREEN : LIGHTGREY, BLACK);
		cout << "New";

		COORDS(1, 0);
		COLOR(sel == 1 ? GREEN : LIGHTGREY, BLACK);
		cout << "Load";

		COORDS(2, 0);
		COLOR(sel == 2 ? GREEN : LIGHTGREY, BLACK);
		cout << "Exit";
	}
	else
	{
		COORDS(0, 0);
		COLOR(sel == 0 ? GREEN : LIGHTGREY, BLACK);
		cout << "Choose  color";

		COORDS(1, 0);
		COLOR(sel == 1 ? GREEN : LIGHTGREY, BLACK);
		cout << "Choose symbol";

		COORDS(2, 1);
		COLOR(sel == 2 ? GREEN : LIGHTGREY, BLACK);
		cout << "Clear table";

		COORDS(3, 3);
		COLOR(sel == 3 ? GREEN : LIGHTGREY, BLACK);
		cout << "Load";

		COORDS(4, 3);
		COLOR(sel == 4 ? GREEN : LIGHTGREY, BLACK);
		cout << "Save";

		COORDS(5, 3);
		COLOR(sel == 5 ? GREEN : LIGHTGREY, BLACK);
		cout << "Exit";
	}

	COLOR(LIGHTGREY, BLACK);
}
//-----------------------------------------------------------------------------------------------
void menu(Cell **filed)
{
	static int sel = 0, choose = 1, count = 0, key = 0;

	while (true)
	{
		showMenu(choose, sel);

		if (choose == 1)
			count = 3;
		else
			count = 6;

		key = getch();
		if (key == 224)
			key = getch();

		if (key == 72 && 0 < sel) // Up
			sel--;
		else if (key == 80 && sel < count - 1) // Down
			sel++;

		else if (key == 13)
		{
			switch (sel)
			{
			case 0:
				if (count == 3)
				{
					newPicture();
					clearMenu();
					choose--;
				}	//New
				else
				{
					cColor();
					
				}
					//cColor();
				break;

			case 1:
				if (count == 3)
				{
				}	//Load 
				else
					//cSymbol();
				break;

			case 2:
				if (count == 3)
				{
					return;
				}	//Exit 
				else
					//clearTable();
				break;

			case 3:
				// Load
				break;

			case 4:
				//Save
				break;

			case 5:
				//Exit
				break;
			}
		}
		else if (key == 9)
			draw();
	}
}