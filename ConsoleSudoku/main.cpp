#include "sudoku.h"

uint8_t OpenSlotsOptionBtn::open_slots_count = 20;

Application* Application::adress = nullptr;

int main()
{
	SetConsoleTitle(L"Sudoku");
	SdkAppl apple;
	apple.ExecHandler();
	return 0;
}