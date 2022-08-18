#include "ConsoleCursore_cmds.h"
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void CursorGoto(const Position& CursorePosition)
{
	SetConsoleCursorPosition(hStdOut, { CursorePosition.x,CursorePosition.y });
}

void conCursoreSet(bool mode, short size)
{
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}