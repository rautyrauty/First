#include "ConsoleCursore_cmds.h"
#include <fstream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

uint16_t SnakeGame();
void SetBestScore(const uint16_t& x)
{
	std::ofstream NewZeroScore("SnakeBestData.txt");
	NewZeroScore << x;
	NewZeroScore.close();
}
uint16_t GiveBestScore()
{
	std::ifstream bestscore("SnakeBestData.txt");
	if (!bestscore.is_open())
	{
		SetBestScore(0);
		std::ifstream bestscore("SnakeBestData.txt");
	}
	uint16_t BestScore;
	bestscore >> BestScore;
	bestscore.close();
	return BestScore;
}

bool GameOver(const uint16_t& tmpScore, const HANDLE& hStdOut)
{
	system("CLS"); // clear screen
	// Номера клавиш
	const uint8_t LEFT = 75;
	const uint8_t RIGHT = 77;
	const uint8_t ENTER = 13;
	// конец нумерации клавиш
	uint16_t BestScore = GiveBestScore();
	if (tmpScore > BestScore) SetBestScore(tmpScore);
	CursorGoto(55, 12);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "GAME OVER.";
	CursorGoto(52, 13);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	std::cout << "Do u wanna retry?";
	bool ActivePosMenu = 0;
	uint16_t pressed_key;
	std::string GameOverChoice[] = { "Ofc yes", "No, return to menu" };
	while (true)
	{
		CursorGoto(50, 15);
		for (int i = 0; i < 2; i++)
		{
			if (i == ActivePosMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			std::cout << GameOverChoice[i] << '\t';
		}
		pressed_key = _getch();
		if (pressed_key == 224) pressed_key = _getch();
		switch (pressed_key)
		{
		case LEFT:
			ActivePosMenu = 0;
			break;
		case RIGHT:
			ActivePosMenu = 1;
			break;
		case ENTER:
			system("CLS"); // clear screen
			return !ActivePosMenu;
		default:
			break;
		}
	}
	system("CLS"); // clear screen
}
void OpenBestScoreView(const HANDLE& hStdOut)
{
	system("CLS"); // clear screen
	// Номера клавиш
	const uint8_t LEFT = 75;
	const uint8_t RIGHT = 77;
	const uint8_t EXIT = 27;
	const uint8_t ENTER = 13;
	// конец нумерации клавиш

	bool ActivePosMenu = 0;
	bool exit_flag = true;

	uint16_t BestScore = GiveBestScore();
	CursorGoto(52, 13);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	std::cout << "What u Wanna do?";
	std::string BestScoreMenu[] = { "Return to Menu", "Clear Score" };
	uint8_t pressed_key;
	while (exit_flag)
	{
		CursorGoto(48, 12);
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "You're best score is " << BestScore;
		CursorGoto(44, 15);
		for (uint8_t i = 0; i < 2; i++)
		{
			if (i == ActivePosMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			std::cout << BestScoreMenu[i] << '\t';
		}
		pressed_key = _getch();
		if (pressed_key == 224) pressed_key = _getch();
		switch (pressed_key)
		{
		case EXIT:
			exit_flag = false;
		case LEFT:
			ActivePosMenu = 0;
			break;
		case RIGHT:
			ActivePosMenu = 1;
			break;
		case ENTER:
			switch (ActivePosMenu) 
			{
			case 0: 
				exit_flag = 0;
				break;
			case 1:
				SetBestScore(0);
				BestScore = 0;
				system("CLS"); // clear screen
				CursorGoto(49, 13);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
				std::cout << "What u Wanna do?";
				break;
			default:
				exit(-200);
			}
			break;
		default:
			break;
		}
	}

	system("CLS"); // clear screen
}
void OpenMenu()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("CLS"); // clear screen
	// Номера клавиш
	const uint8_t EXIT = 27;
	const uint8_t UP = 72;
	const uint8_t DOWN = 80;
	const uint8_t ENTER = 13;
	// конец нумерации клавиш
	uint8_t pressed_key;
	uint8_t ActivePosMenu = 0;
	std::string Menu[] = { "New game","Best session score", "Exit" };
	bool exit_flag = true;
	while (exit_flag)
	{
		conCursoreSet(false, 100); // invis cursore
		CursorGoto(50, 12); // Поставит курсор в середину консоли

		//Вывод меню на экран с выбранной строкой
		for (uint8_t i = 0; i < size(Menu); i++)
		{
			if (i == ActivePosMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			CursorGoto(50, 12 + i);
			std::cout << Menu[i];
		}

		pressed_key = _getch();
		if (pressed_key == 224) pressed_key = _getch();
		switch (pressed_key)
		{
		case EXIT:
			exit_flag = false;
		case DOWN:
			if (ActivePosMenu == size(Menu) - 1) ActivePosMenu = 0;
			else ActivePosMenu++;
			break;
		case UP:
			if (ActivePosMenu == 0) ActivePosMenu = size(Menu) - 1;
			else ActivePosMenu--;
			break;
		case ENTER:
			//ActiveChoice(Menu[ActivePosMenu]); // Отладка
			switch (ActivePosMenu) {
			case 0: // new game
				while (GameOver(SnakeGame(), hStdOut)){ }
				break;
			case 1: // open best score
				OpenBestScoreView(hStdOut);
				break;
			case 2: // exit
				exit_flag = false;
				break;
			default:
				exit(-121);
			}
			break;
		default:
			//std::cout << "code: " << int(pressed_key) << "    "; // Отладка
			break;
		}
	}
}

int main()
{
	OpenMenu();
	_CrtDumpMemoryLeaks();
	return 0;
}