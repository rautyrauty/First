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

CreateMenuBtn::CreateMenuBtn(short x, short y)
	:
	Button("Return", x, y, BACKGROUND_GREEN)
{
}

void CreateMenuBtn::Click(Cursore* crsr)
{
	Application::GetAdress()->SwitchLayout(new Menu());
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


SdkBtn::SdkBtn(Sudoku* sdk, short x, short y) 
	: 
	Button("0", x, y, BACKGROUND_GREEN)
{
	this->sdk = sdk;
	num = 0;
	is_locked = false;
}


void SdkBtn::SetNum(const uint8_t& n)
{
	num = n;
	char new_text[2];
	new_text[0] = char(n + 48);
	new_text[1] = '\n';
	SetText(new_text);
	Render();
}

void SdkBtn::Click(Cursore* crsr)
{

}

DynBtn::DynBtn(short x, short y)
	:
	SdkBtn("0", x, y, BACKGROUND_GREEN)
{}

void DynBtn::Click(Cursore* crsr)
{
	if (num + 1 >= 10) SetNum(0);
	else (SetNum(num + 1));
}

LockedBtn::LockedBtn(const char*& string, short x, short y)
	:
	SdkBtn(string, x, y, BACKGROUND_RED)
{}

void LockedBtn::Click(Cursore * crsr)
{
	MessageBeep(MB_ICONQUESTION);
}