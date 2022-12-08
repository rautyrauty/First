#include "tools.h"

Label::Label(const char* string, short x, short y, WORD color = NULL)
{
	text = nullptr;
	SetText(string);
	SetColor(color);
	this->x = x;
	this->y = y;
	Render();
}

Label::~Label()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, { x,y });
	for (size_t i = 0; text[i] != ' \0'; i += 1) std::cout << ' ';
	delete[] text;
}

void Label::SetText(const char* new_text)
{
	if (text) delete[] text;
	text = new char [256];
	for (uint8_t i = 0; true; i += 1)
	{
		text[i] = new_text[i];
		if (new_text[i] == '\0') break;
	}
}

void Label::SetColor(WORD color)
{
	this->color = color;
}

void Label::Render() const
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
	SetConsoleCursorPosition(hStdOut, { x,y });
	std::cout << text;
}

Button::Button(const char* string, short x, short y, WORD color) 
	: 
	Label(string, x, y, color), 
	dflt_color{color}
{
	flash_countdown = 0;
	flash_lever = false;
}

void Button::ReturnDfltColor()
{
	SetColor(dflt_color);
}

void Button::Flashes()
{
	flash_countdown++;
	Sleep(100);
	if (flash_countdown % 50 == 0)
	{
		if (flash_lever) SetColor(dflt_color);
		else
		{
			if (dflt_color) SetColor(dflt_color | BACKGROUND_INTENSITY);
			else SetColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		}
		flash_lever = !flash_lever;
		Render();
	}
}

bool Layout::IsRendered() const
{
	return is_rendered;
}

Cursore::Cursore(BtnNode* start_nd = nullptr)
{
	crnt_nd = start_nd;
}

void Cursore::SetNode(BtnNode* new_nd)
{
	crnt_nd = new_nd;
}

BtnNode* Cursore::GetNode() const
{
	return crnt_nd;
}

void Cursore::Set(bool mode, const size_t& size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}

Application* Application::GetAdress()
{
	return adress;
}

Application::Application()
{
	adress = this;
}

void Application::SwitchLayout(Layout* lt)
{
	delete crnt_lt;
	crnt_lt = lt;
}

void Application::ExecHandler()
{
	while (true)
	{
		if (not crnt_lt->IsRendered()) crnt_lt->Render();

		if ((GetKeyState(VK_UP)) and (crsr.GetNode()->up))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->up);
		}
		else if ((GetKeyState(VK_DOWN)) and (crsr.GetNode()->down))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->down);
		}
		else if ((GetKeyState(VK_LEFT)) and (crsr.GetNode()->left))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->left);
		}
		else if ((GetKeyState(VK_RIGHT)) and (crsr.GetNode()->right))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->right);
		}
		else if (GetKeyState(VK_RETURN)) // enter
		{
			crsr.GetNode()->btn->Click(&crsr);
		}

		crsr.GetNode()->btn->Flashes();
	}
}