#pragma once
#include <conio.h>
#include <Windows.h>

struct Position {
	Position()
	{
		x = 0;
		y = 0;
	}
	Position(short x,short y)
	{
		this->x = x;
		this->y = y;
	}
	short x;
	short y;
};
void CursorGoto(const Position& CursorePosition);
void conCursoreSet(bool mode, short size);