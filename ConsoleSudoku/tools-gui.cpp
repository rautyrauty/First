#include "tools-gui.h"

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
	RemoveRender();
	if (text) delete[] text;
}

void Label::SetText(const char* new_text)
{
	RemoveRender();
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

void Label::RemoveRender() const
{
	if (text)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hStdOut, { x,y });
		for (size_t i = 0; text[i] != '\0'; i += 1)
		{
			std::cout << ' ';
		}
	}
}

Button::Button(const char* string, short x, short y, WORD color) 
	: 
	Label(string, x, y, color), 
	dflt_color{color}
{
	nd.btn = this;
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

void Button::SetDfltColor()
{
	SetColor(dflt_color);
	Render();
}

WORD Button::GetDfltColor() const
{
	return dflt_color;
}

BtnNode* Button::GetNodeAdress()
{
	return &nd;
}

Cursore::Cursore(BtnNode* start_nd)
{
	current = start_nd;
	blink_countdown = 0;
	blink_lever = false;
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
	current->btn->SetDfltColor();
	blink_countdown = 0;
	blink_lever = false;
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

void Cursore::Click()
{
	current->btn->Click(this);
}

void Cursore::Blink()
{
	Sleep(100);
	if (blink_countdown % 5 == 0)
	{
		if (blink_lever) current->btn->SetDfltColor();
		else
		{
			current->btn->SetColor(current->btn->GetDfltColor() | FOREGROUND_INTENSITY);
		}
		blink_lever = !blink_lever;
		current->btn->Render();
	}
	blink_countdown++;
}

void Cursore::MakeInvisible()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = false;
	structCursoreInfo.dwSize = 1;
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
	system("CLS");
	crnt_lt->Render();
}

void Application::ExecHandler()
{
	crnt_lt->Render();
	crsr.MakeInvisible();
	while (true)
	{
		if ((GetAsyncKeyState(VK_UP)) and (crsr.IsBtnExist(Cursore::Dir::up)))
		{
			crsr.Move(Cursore::Dir::up);
		}
		else if ((GetAsyncKeyState(VK_DOWN)) and (crsr.IsBtnExist(Cursore::Dir::down)))
		{
			crsr.Move(Cursore::Dir::down);
		}
		else if ((GetAsyncKeyState(VK_LEFT)) and (crsr.IsBtnExist(Cursore::Dir::left)))
		{
			crsr.Move(Cursore::Dir::left);
		}
		else if ((GetAsyncKeyState(VK_RIGHT)) and (crsr.IsBtnExist(Cursore::Dir::right)))
		{
			crsr.Move(Cursore::Dir::right);
		}
		else if (GetAsyncKeyState(VK_RETURN)) // enter
		{
			crsr.Click();
		}

		crsr.Blink();
	}
}