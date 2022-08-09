#include "ConsoleCursore_cmds.h"
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void CursorGoto(const short& x, const short& y)
{
	SetConsoleCursorPosition(hStdOut, { x,y });
}

void conCursoreSet(bool mode, short size)
{
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}