#include "sudoku.h"
uint8_t OpenSlotsOptionBtn::GetCount()
{
	return open_slots_count;
}
OpenSlotsOptionBtn::OpenSlotsOptionBtn(short x, short y) 
	: 
	Button("20", x, y)
{
	open_slots_count = 20;
}

void OpenSlotsOptionBtn::Click(Cursore* crsr)
{
	open_slots_count += 1;
	if (open_slots_count > 81) open_slots_count = 0;

	char new_text[3];
	if (open_slots_count < 10)
	{
		new_text[0] = char((open_slots_count % 10) + 48);
		new_text[1] = '\0';
	}
	else
	{
		new_text[0] = char((open_slots_count / 10 % 10) + 48);
		new_text[1] = char((open_slots_count % 10) + 48);
	}
	new_text[2] = '\0';
	SetText(new_text);
	Render();
}

CreateSudokuBtn::CreateSudokuBtn(short x, short y)
	: 
	Button("Play!", x, y, BACKGROUND_GREEN)
{}

void CreateSudokuBtn::Click(Cursore* crsr)
{
	Application::GetAdress()->SwitchLayout(new Sudoku(OpenSlotsOptionBtn::GetCount()));
}

ExitBtn::ExitBtn(short x, short y) 
	:
	Button("Exit", x, y, BACKGROUND_RED)
{}

void ExitBtn::Click(Cursore* crsr)
{
	exit(0);
}

CheckBtn::CheckBtn(Sudoku* sdk, short x, short y) 
	: 
	Button("Check", x, y, NULL)
{
	this->sdk = sdk;
}

void CheckBtn::Click(Cursore* crsr)
{
	sdk->Check();
}

GetSolutionBtn::GetSolutionBtn(Sudoku* sdk, short x, short y)
	:
	Button("Get Solution", x, y, BACKGROUND_BLUE)
{
	this->sdk = sdk;
}

void GetSolutionBtn::Click(Cursore* crsr)
{
	sdk->GetSolution();
}

void SdkBtn::SetNum(const uint8_t& n)
{
	num = n;
	char new_text[2];
	new_text[0] = char(n + 48);
	new_text[1] = '\n';
	SetText(new_text);
}

SdkBtn::SdkBtn(const char*& string, short x, short y, WORD color)
	:
	Button(string, x, y, color)
{
	num = string[0];
}

DynBtn::DynBtn(const char*& string, short x, short y)
	:
	SdkBtn(string, x, y, BACKGROUND_GREEN)
{

}

void DynBtn::Flashes()
{
	flash_countdown++;
	Sleep(100);
	if (flash_countdown % 50 == 0)
	{
		if (flash_lever) SetColor(BACKGROUND_GREEN);
		else SetColor(BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		flash_lever = !flash_lever;
		Render();
	}
}
