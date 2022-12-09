#include "tools.h"

Label::Label(const char* string, short x, short y, WORD color)
{
	text = nullptr;
	this->x = x;
	this->y = y;
	SetText(string);
	SetColor(color);
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
	Render();
}

void Label::SetColor(WORD color)
{
	this->color = color;
	Render();
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
	nd.btn = this;
	flash_countdown = 0;
	flash_lever = false;
}

void Button::Connect(Button& first, Button& second, ConType ct)
{
	switch (ct)
	{
	case (ConType::UpDown):
		first.nd.down = &(second.nd);
		second.nd.up = &(first.nd);
		break;
	case (ConType::LeftRight):
		first.nd.right = &(second.nd);
		second.nd.left = &(first.nd);
		break;
	}
}

void Button::ReturnDfltColor()
{
	SetColor(dflt_color);
	Render();
}

void Button::Flashes()
{
	Sleep(100);
	if (flash_countdown % 5 == 0)
	{
		if (flash_lever) SetColor(dflt_color);
		else
		{
			if (dflt_color) SetColor(dflt_color | FOREGROUND_INTENSITY);
			else SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		flash_lever = !flash_lever;
		Render();
	}
	flash_countdown++;
}

void Button::ResetFlashCounter()
{
	flash_countdown = 0;
	flash_lever = false;
}

BtnNode* Button::GetNodeAdress()
{
	return &nd;
}

bool Layout::IsRendered() const
{
	return is_rendered;
}

Cursore::Cursore(BtnNode* start_nd)
{
	current = start_nd;
}

void Cursore::SetNode(BtnNode* new_nd)
{
	current = new_nd;
}

bool Cursore::IsBtnExist(Dir d) const
{
	switch (d)
	{
	case Dir::up:
		return current->up;
	case Dir::down:
		return current->down;
	case Dir::left:
		return current->left;
	case Dir::right:
		return current->right;
	}
}

void Cursore::Move(Dir d)
{
	switch (d)
	{
	case Dir::up:
		current = current->up;
		return;
	case Dir::down:
		current = current->down;
		return;
	case Dir::left:
		current = current->left;
		return;
	case Dir::right:
		current = current->right;
		return;
	}
}

void Cursore::MakeInvisible()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = false;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}

Application* Application::GetAdress()
{
	return adress;
}

void Application::SwitchLayout(Layout* lt)
{
	delete crnt_lt;
	crnt_lt = lt;
	crsr.SetNode(lt->GetStartNode());
}

void Application::ExecHandler()
{
	crsr.MakeInvisible();
	while (true)
	{
		if (not crnt_lt->IsRendered()) crnt_lt->Render();

		if ((GetAsyncKeyState(VK_UP)) and (crsr.IsBtnExist(Cursore::Dir::up)))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->up);
		}
		else if ((GetAsyncKeyState(VK_DOWN)) and (crsr.IsBtnExist(Cursore::Dir::down)))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->down);
		}
		else if ((GetAsyncKeyState(VK_LEFT)) and (crsr.IsBtnExist(Cursore::Dir::left)))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->left);
		}
		else if ((GetAsyncKeyState(VK_RIGHT)) and (crsr.IsBtnExist(Cursore::Dir::right)))
		{
			crsr.GetNode()->btn->ReturnDfltColor();
			crsr.SetNode(crsr.GetNode()->right);
		}
		else if (GetAsyncKeyState(VK_RETURN)) // enter
		{
			crsr.GetNode()->btn->Click(&crsr);
		}

		crsr.GetNode()->btn->Flashes();
	}
}