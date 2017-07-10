#include <iostream>
//#include <Windows.h>
#include <conio.h>
//-----------------------------------------------------------------------------------------------

//#include "Cursor.h"
#include "draw.h"
//-----------------------------------------------------------------------------------------------
extern int fg, bg;
extern char sym;
extern bool color;

extern char path[_MAX_PATH];
extern CELL field[row][col];
//-----------------------------------------------------------------------------------------------
Command menu(bool first, int &sel)
{
	int count;

	Cursor(false);

	while (true)
	{
		showMenu(first, sel);

		if (first)
			count = 3;
		else
			count = 6;

		int key = getch();
		if (key == 224)
			key = getch();

		if (key == 72 && 0 < sel) // Up
			sel--;
		else if (key == 80 && sel < count - 1) // Down
			sel++;
		else if (key == 13)
		{
			if (first)
			{
				switch (sel)
				{
				case 0:
					return cNew;
				case 1:
					return cLoad;
				case 2:
					return cExit;
				}
			}
			else
			{
				switch (sel)
				{
				case 0:
					return cColors;
				case 1:
					return cSymbols;
				case 2:
					return cClear;
				case 3:
					return cLoad;
				case 4:
					return cSave;
				case 5:
					return cExit;
				}
			}
		}
		else if (key == 9) // Tab
			return cDraw;
	}
}
//-----------------------------------------------------------------------------------------------
void frame()
{
	COORDS(rowS - 1, colS - 1);

	for (short c = 0; c < col + 2; c++)
		cout << char(178);

	for (short r = 0; r < row; r++)
	{
		COORDS(r + rowS, colS - 1);
		cout << char(178);

		for (short c = 0; c < col; c++)
		{
			CELL *f = &field[r][c];
//			f->symbol = sym;
//			f->fg = Colors(fg);
//			f->bg = Colors(bg);

			drawData(f->symbol, (Colors)f->fg, (Colors)f->bg);
		}

		cout << char(178);
	}

	COORDS(rowS + row, colS - 1);

	for (short c = 0; c < col + 2; c++)
		cout << char(178);
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
	COLOR(LIGHTGREY, BLACK);
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
//	symbols();

	while (true)
	{
		symbols();

		COORDS(row, col);
		if (sym[sel] % 2 == 0 || sym[sel] % 2 == 1)
			COLOR(GREEN, BLACK);

		cout << char(sym[sel]);

		COLOR(LIGHTGREY, BLACK);

		key = getch();
		if (key == 224)
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
		COORDS(i, colS);
		for (short j = colS; j < colF; j++)
		{
			cout << " ";
		}
	}
}
//-----------------------------------------------------------------------------------------------
void clearTable()
{
	for (short r = 0; r < row; r++)
	{
		for (short c = 0; c < col; c++)
		{
			CELL *f = &field[r][c];
			f->symbol = ' ';
			f->fg = BLACK;
			f->bg = BLACK;

		}
	}
}
//-----------------------------------------------------------------------------------------------
void ShowSymCol()
{
	symbols();
	colors();
}
//-----------------------------------------------------------------------------------------------
void draw(char sym, int fg, int bg)
{
	int key = 0;
	short r = 0, c = 0;
	while (true)
	{
		COORDS(rowS + r, colS + c);

		key = getch();
		if (key == 224)
			key = getch();

		if (key == 72 && r > 0) // Up
			r--;
		else if (key == 80 && r < row - 1) // Down
			r++;
		else if (key == 75 && c > 0) // Left
			c--;
		else if (key == 77 && c < col - 1) // Right
			c++;
		else if (key == 32) // enter 13 space 32
		{
			CELL *f = &field[r][c];
			f->symbol = sym;
			f->fg = (Colors)fg;
			f->bg = (Colors)bg;
			//f->fg = fg & 0xF;
			//f->bg = bg & 0xF;

			drawData(f->symbol, (Colors)f->fg, (Colors)f->bg);
		}
		else if (key == 83) // backspace 8 del 83
			cout << " ";
		else if (key == 9)
		{
			return;
		}
	}
}
//-----------------------------------------------------------------------------------------------
void showMenu(bool first, int sel)
{
	clearMenu();

	if (first)
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
		COLOR((sel == 0 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Choose  color";

		COORDS(1, 0);
		COLOR((sel == 1 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Choose symbol";

		COORDS(2, 1);
		COLOR((sel == 2 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Clear table";

		COORDS(3, 3);
		COLOR((sel == 3 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Load";

		COORDS(4, 3);
		COLOR((sel == 4 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Save";

		COORDS(5, 3);
		COLOR((sel == 5 && color == true) ? GREEN : LIGHTGREY, BLACK);
		cout << "Exit";
	}

	COLOR(LIGHTGREY, BLACK);
}
//-----------------------------------------------------------------------------------------------
#define TAG "APF"

bool save(char *FileName)
{
	char newpath[_MAX_PATH];

	strcpy(newpath, path);
	strcat(newpath, "\\");
	strcat(newpath, FileName);
	
	FILE *f = fopen(newpath, "wb");
	if (f == NULL)
		return false;

	bool ret = true;
/*
	for (size_t i = 0; ret && i < row; i++)
		for (size_t j = 0; j < col; j++)
			if (EOF == fwrite(&field[i][j], sizeof(CELL), 1, f))
			{
				ret = false;
				break;
			}
*/
	if (EOF == fwrite(TAG, 3, 1, f))
	{
		ret = false;
		goto exit;
	}

	if (EOF == fwrite(&row, sizeof(row), 1, f))
	{
		ret = false;
		goto exit;
	}

	if (EOF == fwrite(&col, sizeof(col), 1, f))
	{
		ret = false;
		goto exit;
	}

	if (EOF == fwrite(field, sizeof(CELL), row*col, f))
		ret = false;

exit:
	fclose(f);

	return ret;
}
//--------------------------------------------------------------------
bool load(char *FileName)
{
	char newpath[_MAX_PATH];

	strcpy(newpath, path);
	strcat(newpath, "\\");
	strcat(newpath, FileName);

	FILE *f = fopen(newpath, "rb");

	if (f == NULL)
		return false;

	bool ret = true;
	/*
	for (size_t i = 0; ret && i < row; i++)
	{
	for (size_t j = 0; j < col; j++)
	{
	if (EOF == fread(&field[i][j], sizeof(CELL), 1, f))
	{
	ret = false;
	break;
	}
	}
	}
	*/
	char tag[3];
	if (EOF == fread(tag, 3, 1, f))
	{
		ret = false;
		goto exit;
	}

	if (strncmp(tag, TAG, 3) != 0)
	{
		ret = false;
		goto exit;
	}

	int r;
	if (EOF == fread(&r, sizeof(row), 1, f))
	{
		ret = false;
		goto exit;
	}

	if (r != row)
	{
		ret = false;
		goto exit;
	}

	int c;
	if (EOF == fread(&c, sizeof(col), 1, f))
	{
		ret = false;
		goto exit;
	}

	if (c != col)
	{
		ret = false;
		goto exit;
	}

	if (EOF == fread(field, sizeof(CELL), row*col, f))
		ret = false;

exit:
	fclose(f);

	return ret;
}
//--------------------------------------------------------------------
void Cursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
//----------------------------------------------------------------------
char * AskFileName(char *Prompt)
{
	static char Buff[_MAX_PATH];

	COORDS(28, 0);
	cout << Prompt;
	Cursor(true);
	cin >> Buff;
	Cursor(false);
	COORDS(28, 0);
	for (size_t i = 0; i < 70; i++)
	{
		cout << " ";
	}

	return Buff;
}
//----------------------------------------------------------------------
