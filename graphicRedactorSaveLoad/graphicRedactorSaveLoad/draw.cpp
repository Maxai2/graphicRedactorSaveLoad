#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "draw.h"
//-----------------------------------------------------------------------------------------------
void showMenu(int choose, int sel);
void newPicture();
void clearMenu();
char cSymbol();
int cColorfg();
int cColorbg();
void draw(CELL field[row][col], char sym = '*', int fg = LIGHTGREY, int bg = BLACK);
void clearColorRedact();
void clearTable();
//-----------------------------------------------------------------------------------------------
int fg = 7, bg = 0;
char sym = '*';
//-----------------------------------------------------------------------------------------------
void menu(CELL field[row][col])
{
	static int sel = 0, choose = 1, count = 0, key = 0;
	//	_setcursortype(_NOCURSOR);
	//	ShowCursor(0);

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
					fg = cColorfg();
					bg = cColorbg();
					clearColorRedact();
				}
				//cColorfgbg();
				break;

			case 1:
				if (count == 3)
				{
				}	//Load 
				else
					sym = cSymbol();
				//cSymbol();
				break;

			case 2:
				if (count == 3)
					return;
				//Exit 
				else
					clearTable();
				break;

			case 3:
				// Load
				break;

			case 4:
				//Save
				break;

			case 5:
				return;
				//Exit
				break;
			}
		}
		else if (key == 9) // Tab
			draw(field, sym, fg, bg);
	}
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
	short row = 9, col = 5;
	COORDS(row, 2);
	cout << "Symbols:";
	row++;
	for (int i = 34; i <= 126; i++)
	{
		if (i == 34 || i == 36 || 40 <= i && i <= 43 || 45 <= i && i <= 47)
		{
			COORDS(row, col);
			cout << char(i) << endl;
			row++;
		}
		else if (i == 60 || i == 62 || i == 64 || i == 92 || i == 94 || i == 95 || i == 124 || i == 126)
		{
			COORDS(row, col);
			cout << char(i) << endl;
			row++;
		}
	}
}
//-----------------------------------------------------------------------------------------------
void clearColorRedact()
{
	for (size_t i = 1; i < 3; i++)
	{
		for (size_t j = 0; j < 60; j++)
		{
			COORDS(i, j);

			cout << " ";
		}
	}
}
//-----------------------------------------------------------------------------------------------
int cColorfg()
{
	COORDS(1, 20);
	int col;

	for (int i = 20; i < 46; i++)
		cout << " ";

	COORDS(1, 20);
	COLOR(LIGHTGREY, BLACK);
	cout << "Input number of color for forground: ";
	cin >> col;

	return col;
}
//-----------------------------------------------------------------------------------------------
int cColorbg()
{
	COORDS(2, 20);
	int col;

	for (int i = 20; i < 46; i++)
		cout << " ";

	COORDS(2, 20);
	COLOR(LIGHTGREY, BLACK);
	cout << "Input number of color for background: ";
	cin >> col;

	return col;
}
//-----------------------------------------------------------------------------------------------
char cSymbol()
{
	int key, sel = 0;
	short row = 10, col = 5;
	int sym[17] = { 34, 36, 40, 41, 42, 43, 45, 46, 47, 60, 62, 64, 92, 94, 95, 124, 126 };

	while (true)
	{
		symbols();

		COORDS(row, col);

		if (sym[sel] % 2 == 0)
		{
			COLOR(CYAN, BLACK);
			cout << char(sym[sel]);
		}

		COORDS(row, col);

		COLOR(LIGHTGREY, BLACK);
		if (sym[sel] % 2 == 1)
		{
			COLOR(CYAN, BLACK);
			cout << char(sym[sel]);
		}
		COLOR(LIGHTGREY, BLACK);

		key = getch();
		if (key == 0)
			key = getch();

		if (key == 72 && row >= 11) // Up
		{
			sel--;
			row--;
		}
		else if (key == 80 && row <= 25) // Down
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
void clearTable()
{
	short rowS = 8, rowF = 25, colS = 19, colF = 66;

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
void draw(CELL field[row][col], char sym, int fg, int bg)
{
	int key = 0;
	short rowD = 8, colD = 19;
	while (true)
	{
		COORDS(rowD, colD);

		key = getch();
		if (key == 224)
			key = getch();

		if (key == 72 && rowD > 8) // Up
			rowD--;
		else if (key == 80 && rowD < 24) // Down
			rowD++;
		else if (key == 75 && colD > 19) // Left
			colD--;
		else if (key == 77 && colD < 65) // Right
			colD++;
		else if (key == 32) // enter 13 space 32
		{
			field[rowD][colD].symbol = sym;
			field[rowD][colD].fg = Colors(fg);
			field[rowD][colD].bg = Colors(bg);

			drawData(field[rowD][colD].symbol, field[rowD][colD].fg, field[rowD][colD].bg);
		}
		else if (key == 83) // backspace 8 del 83
			cout << " ";
		else if (key == 9)
			menu(field);
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
