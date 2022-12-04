#include "sudoku.h"
OpenSlotsOptionBtn::OpenSlotsOptionBtn(const char*& string, short x, short y, WORD color = NULL) : Button(string, x, y, color)
{
	open_slots_count = 3;
}

uint8_t OpenSlotsOptionBtn::GetOpenSlots()
{
	return open_slots_count;
}

void OpenSlotsOptionBtn::Flashes()
{
	flash_countdown++;
	Sleep(100);
	if (flash_countdown % 50 == 0)
	{
		if (flash_lever) SetColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		else SetColor(BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		flash_lever = !flash_lever;
	}
}

void OpenSlotsOptionBtn::Click(Cursore* crsr)
{
	open_slots_count += 1;
	if (open_slots_count > 81) open_slots_count = 0;
}

ExitBtn::ExitBtn(const char*& string, short x, short y, WORD color = NULL) : Button(string, x, y, color) {}

void ExitBtn::Flashes()
{
	flash_countdown++;
	Sleep(100);
	if (flash_countdown % 50 == 0)
	{
		if (flash_lever) SetColor(NULL);
		else SetColor(BACKGROUND_RED | BACKGROUND_INTENSITY);
		flash_lever = !flash_lever;
	}
}

void ExitBtn::Click(Cursore* crsr)
{
	exit(0);
}
