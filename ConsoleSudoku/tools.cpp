#include "tools.h"

void Label::Render() const
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
	SetConsoleCursorPosition(hStdOut, { x,y });
	std::cout << text;
}

Label::Label(const char*& string, short x, short y, WORD color = NULL)
{
	SetText(string);
	SetColor(color);
	Render();

	this->x = x;
	this->y = y;
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

void Cursore::Set(bool mode, const size_t& size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursoreInfo;
	structCursoreInfo.bVisible = mode;
	structCursoreInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursoreInfo);
}

void Cursore::ActionHandler()
{
	while (true)
	{
		if (not crnt_lt->IsRendered()) crnt_lt->Render();

		if ((GetKeyState(VK_UP)) and (crnt_nd->up))
		{
			crnt_nd->btn->SwitchColor(NULL);
			crnt_nd = crnt_nd->up;
		}
		else if ((GetKeyState(VK_DOWN)) and (crnt_nd->down))
		{
			crnt_nd->btn->SwitchColor(NULL);
			crnt_nd = crnt_nd->down;
		}
		else if ((GetKeyState(VK_LEFT)) and (crnt_nd->left))
		{
			crnt_nd->btn->SwitchColor(NULL);
			crnt_nd = crnt_nd->left;
		}
		else if ((GetKeyState(VK_RIGHT)) and (crnt_nd->right))
		{
			crnt_nd->btn->SwitchColor(NULL);
			crnt_nd = crnt_nd->right;
		}
		else if (GetKeyState(VK_RETURN)) // enter
		{
			crnt_nd->btn->Click(this);
		}

		crnt_nd->btn->Flashes();
	}
}