#pragma once


class button
{
	char* text;
	size_t size;
	button* up;
	button* down;
	button* left;
	button* right;
	size_t x;
	size_t y;
public:
	virtual void Click() = 0;
	void SetColor(_In_ HANDLE hConsoleOutput, _In_ WORD wAttributes)
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
};



