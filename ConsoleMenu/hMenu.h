#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

extern HANDLE hStdOut;

void goto_XY(const short& x, const short& y);
void conCursoreSet(bool mode, short size);