//#include <windows.h>
//-----------------------------------------------
#include <io.h>
#include "draw.h"

char path[_MAX_PATH];
CELL field[row][col];
int fg = 7, bg = 0;
char sym = '*';
bool color = true;
//----------------------------------------------------------
void main(int argc, char *argv[])
{
	strcpy(path, argv[0]);
	char *s = strrchr(path, '\\');
	*s = 0;
//	strcat(path, "\\picture.dat");
	//sprintf(path, "%s%s", getenv("USERPROFILE"), "//Desktop//Example//Task.dat");

/*
	_finddata_t fd;
	int r = _findfirst(path, &fd);
	
	if (r != -1)
	{
		_findclose(r);
		load(field);
	}
*/
	int sel = 0;
	//cout << sizeof(CELL);

//	system("pause");

	bool bFirst = true;
	while (true)
	{
		Command res = menu(bFirst, sel);
		if (bFirst)
		{
			bFirst = false;
			clearMenu();
			ShowSymCol();
			sel = 0;
		}

		bool bDraw = false;

		switch (res)
		{
		case cNew:
			clearTable();
			frame();
			bDraw = true;
			break;
		case cColors:
			color = false;
			showMenu(false, sel);
			Cursor(true);
			fg = cColorfg();
			bg = cColorbg();
			clearColorRedact();
			color = true;
			Cursor(false);
			break;
		case cSymbols:
			color = false;
			showMenu(false, sel);
			sym = cSymbol();
			color = true;
			symbols();
			break;
		case cClear:
			clearTable();
			frame();
			bDraw = true;
			break;
		case cLoad:
		{
			char *s = AskFileName("Input file name for load >");
			if (*s)
				load(s);
			frame();
			bDraw = true;
			break;
		}
		case cSave:
		{
			char *s = AskFileName("Input file name for save >");
			if (*s)
				save(s);
			break;
		}
		case cExit:
			return;
		case cDraw:
			bDraw = true;
			break;
		}

		if (bDraw)
		{
			color = false;
			showMenu(false, sel);
			Cursor(true);
			draw(sym, fg, bg);
			color = true;
		}
	}
}
//----------------------------------------------------------------------------------
