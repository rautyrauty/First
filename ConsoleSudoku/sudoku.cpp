#include "sudoku.h"
uint8_t OpenSlotsOptionBtn::GetCount()
{
	return open_slots_count;
}
OpenSlotsOptionBtn::OpenSlotsOptionBtn(short x, short y) 
	: 
	Button("20", x, y)
{
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
	Button("Play!", x, y, FOREGROUND_GREEN)
{}

void CreateSudokuBtn::Click(Cursore* crsr)
{
	//Application::GetAdress()->SwitchLayout(new Sudoku(OpenSlotsOptionBtn::GetCount()));
	MessageBeep(MB_ICONQUESTION);
}

ExitBtn::ExitBtn(short x, short y) 
	:
	Button("Exit", x, y, FOREGROUND_RED)
{}

void ExitBtn::Click(Cursore* crsr)
{
	exit(0);
}
//
//CreateMenuBtn::CreateMenuBtn(short x, short y)
//	:
//	Button("Return", x, y, FOREGROUND_GREEN)
//{
//}
//
//void CreateMenuBtn::Click(Cursore* crsr)
//{
//	Application::GetAdress()->SwitchLayout(new Menu());
//}
//
//CheckBtn::CheckBtn(Sudoku* sdk, short x, short y) 
//	: 
//	Button("Check", x, y, NULL)
//{
//	this->sdk = sdk;
//}
//
//void CheckBtn::Click(Cursore* crsr)
//{
//	sdk->Check();
//}
//
//GetSolutionBtn::GetSolutionBtn(Sudoku* sdk, short x, short y)
//	:
//	Button("Get Solution", x, y, FOREGROUND_BLUE)
//{
//	this->sdk = sdk;
//}
//
//void GetSolutionBtn::Click(Cursore* crsr)
//{
//	sdk->GetSolution();
//}
//
//DevModeBtn::DevModeBtn(Sudoku* sdk, short x, short y)
//	:
//	Button("Developer Mode", x, y, FOREGROUND_BLUE)
//{
//	this->sdk = sdk;
//}
//
//void DevModeBtn::Click(Cursore* crsr)
//{
//	sdk->SwitchDevMode();
//}
//
//SdkBtn::SdkBtn(Sudoku* sdk, short x, short y) 
//	: 
//	Button("0", x, y, FOREGROUND_GREEN)
//{
//	this->sdk = sdk;
//	num = 0;
//	is_locked = false;
//}
//
//
//void SdkBtn::LockUp()
//{
//	is_locked = !is_locked;
//}
//
//void SdkBtn::SetNum(const uint8_t& n)
//{
//	num = n;
//	char new_text[2];
//	new_text[0] = char(n + 48);
//	new_text[1] = '\n';
//	SetText(new_text);
//	Render();
//}
//
//bool SdkBtn::IsLocked() const
//{
//	return is_locked;
//}
//
//void SdkBtn::Click(Cursore* crsr)
//{
//	if (is_locked) MessageBeep(MB_ICONQUESTION);
//	else
//	{
//		if (num + 1 >= 10) SetNum(0);
//		else (SetNum(num + 1));
//	}
//}

Menu::Menu() : play{0,0}, option { 20, 0 }, ex{0,1}
{
	Button::Connect(play, option, ConType::LeftRight);
	Button::Connect(play, ex, ConType::UpDown);
}

void Menu::Render()
{
	system("CLS");
	play.Render();
	option.Render();
	ex.Render();
	is_rendered = true;
}

BtnNode* Menu::GetStartNode()
{
	return play.GetNodeAdress();
}

uint8_t Menu::GetOpenSlotsCount() const
{
	return option.GetCount();
}

Layout* SdkAppl::CreateStartLayout()
{
	return (new Menu);
}

SdkAppl::SdkAppl()
{
	adress = this;
	crnt_lt = CreateStartLayout();
	crsr.SetNode(crnt_lt->GetStartNode());
}