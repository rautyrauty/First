#include "tools.h"

Label::Label(const char*& string, short x, short y, WORD color = NULL)
{
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

void Label::SetText(const char*& new_text)
{
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

Button::Button(const char*& string, short x, short y, WORD color) : Label(string, x, y, color)
{
	flash_countdown = 0;
}

SwitchLtBtn::SwitchLtBtn(const char*& string, short x, short y, WORD color = NULL) : Button(string, x, y, color) {}

void SwitchLtBtn::SetLayout(Layout* lt)
{
	this->lt = lt;
}

void SwitchLtBtn::Flashes()
{
	flash_countdown++;
	if (flash_countdown % 7 == 0)
	{
		if (flash_lever) SetColor(NULL);
		else SetColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	}
}

void SwitchLtBtn::Click(Cursore* crsr)
{
	crsr->SetLayout(lt);
	crsr->SetNode(lt->GetStartNode());
}


void Cursore::SetLayout(Layout* new_lt)
{
	crnt_lt = new_lt;
}

void Cursore::SetNode(BtnNode* new_nd)
{
	crnt_nd = new_nd;
}

Cursore::Cursore(Layout* start_lt, BtnNode* start_nd)
{
	SetLayout(start_lt);
	if (start_nd) SetNode(start_nd);
	else SetNode(start_lt->GetStartNode());
}

void Cursore::Set(bool mode, const size_t& size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}

void Cursore::ExecActionHandler()
{
	while (true)
	{
		if (not crnt_lt->IsRendered()) crnt_lt->Render();

		if ((GetKeyState(VK_UP)) and (crnt_nd->up))
		{
			crnt_nd->btn->SetColor(NULL);
			crnt_nd = crnt_nd->up;
		}
		else if ((GetKeyState(VK_DOWN)) and (crnt_nd->down))
		{
			crnt_nd->btn->SetColor(NULL);
			crnt_nd = crnt_nd->down;
		}
		else if ((GetKeyState(VK_LEFT)) and (crnt_nd->left))
		{
			crnt_nd->btn->SetColor(NULL);
			crnt_nd = crnt_nd->left;
		}
		else if ((GetKeyState(VK_RIGHT)) and (crnt_nd->right))
		{
			crnt_nd->btn->SetColor(NULL);
			crnt_nd = crnt_nd->right;
		}
		else if (GetKeyState(VK_RETURN)) // enter
		{
			crnt_nd->btn->Click(this);
		}

		crnt_nd->btn->Flashes();
	}
}

bool Layout::IsRendered() const
{
	return is_rendered;
}


