#include "sudoku-gui.h"

uint8_t OpenSlotsOptionBtn::open_slots_count = 20;

Application* Application::adress = nullptr;

uint8_t SdkSizeOptionBtn::size = 9;
int main()
{
	SetConsoleTitle(L"Sudoku");
	SdkAppl apple;
	apple.ExecHandler();
	return 0;
}