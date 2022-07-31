#include "hMenu.h"

const int EXIT = 27;
const int UP = 72;
const int DOWN = 80;
const int ENTER = 13;

void ActiveChoice(std::string& choice)
{
	system("CLS");
	goto_XY(50, 14);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "User choose " << choice;
	_getch();
	system("CLS");
}

int main()
{
	system("CLS");
	conCursoreSet(false, 100);
	int ch;
	std::string Menu[] = { "New game","Saves", "Options", "Exit" };
	int ActiveMenu = 0;	
	int x = 50, y = 12;
	
	while ("true")
	{
		conCursoreSet(false, 100);
		goto_XY(x, y);
		for (int i = 0; i < size(Menu); i++)
		{
			if (i == ActiveMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			goto_XY(x, y + i);
			std::cout << Menu[i];
		}
		ch = _getch();
		if (ch==224) ch = _getch();
		switch (ch)
		{
		case EXIT:
			exit(0);
		case DOWN:
			if (ActiveMenu == size(Menu)-1) ActiveMenu = 0;
			else ActiveMenu++;
			break;
		case UP:
			if (ActiveMenu == 0) ActiveMenu = size(Menu)-1;
			else ActiveMenu--;
			break;
		case ENTER:
			if (ActiveMenu == size(Menu) - 1) exit(0);
			ActiveChoice(Menu[ActiveMenu]);
			break;
		default:
			//std::cout << "code: " << ch << "    "; // Отладка
			break;
		}
	}
	_getch();
	return 0;
}