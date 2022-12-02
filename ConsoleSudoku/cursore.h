#pragma once

#include <conio.h>
#include <Windows.h>

class cursore
{
	size_t x;
	size_t y;

	void Goto(const size_t& x, const size_t& y);
	void Set(bool mode, const size_t& size);
};