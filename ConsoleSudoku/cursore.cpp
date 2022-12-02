#include "cursore.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void Goto(const short& x, const short& y)
{
	SetConsoleCursorPosition(hStdOut, { x,y });
}
void Set(bool mode, const size_t& size)
{
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}