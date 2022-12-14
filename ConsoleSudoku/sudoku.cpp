#include "sudoku-gui.h"


// default options
uint8_t OpenSlotsOptionBtn::open_slots_count = 81;

bool DevModeBtn::dev = false;


uint8_t OpenSlotsOptionBtn::GetCount()
{
	return open_slots_count;
}

OpenSlotsOptionBtn::OpenSlotsOptionBtn(short x, short y) 
	: 
	Button(open_slots_count, x, y)
{
}

void OpenSlotsOptionBtn::Click(Cursore* crsr)
{
	open_slots_count += 1;
	if (open_slots_count > 81) open_slots_count = 0;

	char new_text[3];
	if (open_slots_count < 10)
	{
		new_text[0] = char(open_slots_count + 48);
		new_text[1] = '\0';
	}
	else
	{
		new_text[0] = char((open_slots_count / 10 % 10) + 48);
		new_text[1] = char((open_slots_count % 10) + 48);
	}
	new_text[2] = '\0';
	SetText(new_text);
}

CreateSudokuBtn::CreateSudokuBtn(short x, short y)
	: 
	Button("Play!", x, y, FOREGROUND_GREEN)
{}

void CreateSudokuBtn::Click(Cursore* crsr)
{
	Application::GetAdress()->SwitchLayout(new Sudoku(OpenSlotsOptionBtn::GetCount()));
	//MessageBeep(0);
}

ExitBtn::ExitBtn(short x, short y) 
	:
	Button("Exit", x, y, FOREGROUND_RED)
{}

void ExitBtn::Click(Cursore* crsr)
{
	exit(0);
}

Menu::Menu()
	:
	play{ 40,12 },
	ex{ 40,14 },
	os{ 77, 12 },
	about_open_slots{ "Count open slots setting: " ,50,12 }
{
	Button::Connect(play, os, ConType::LeftRight);
	Button::Connect(play, ex, ConType::UpDown);
}

void Menu::Render() const
{
	system("CLS");
	play.Render();
	os.Render();
	ex.Render();
	about_open_slots.Render();
}

BtnNode* Menu::GetStartNode()
{
	return play.GetNodeAdress();
}

uint8_t Menu::GetOpenSlotsCount() const
{
	return os.GetCount();
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
	srand(time(0));
}

//sdk

CreateMenuBtn::CreateMenuBtn(short x, short y)
	:
	Button("Return", x, y, FOREGROUND_GREEN)
{
}

void CreateMenuBtn::Click(Cursore* crsr)
{
	Application::GetAdress()->SwitchLayout(new Menu());
}

CheckBtn::CheckBtn(Sudoku* sdk, short x, short y) 
	: 
	Button("Check", x, y)
{
	this->sdk = sdk;
}

void CheckBtn::Click(Cursore* crsr)
{
	sdk->Check();
}

GetSolutionBtn::GetSolutionBtn(Sudoku* sdk, short x, short y)
	:
	Button("Get Solution", x, y, NULL)
{
	this->sdk = sdk;
}

void GetSolutionBtn::Click(Cursore* crsr)
{
	sdk->GetSolution();
}

DevModeBtn::DevModeBtn(short x, short y)
	:
	Button("Dev Mode", x, y, FOREGROUND_BLUE)
{
}

void DevModeBtn::Click(Cursore* crsr)
{
	dev = !dev;
}

bool DevModeBtn::GiveDevStatus()
{
	return dev;
}

SdkBtn::SdkBtn(short x, short y)
	:
	Button("0", x, y, FOREGROUND_GREEN)
{
	is_locked = false;
	digit = 0;
}

SdkBtn::SdkBtn(uint8_t d, short x, short y)
	:
	Button(d, x, y, FOREGROUND_RED)
{
	is_locked = true;
	digit = d;
}


void SdkBtn::LockUp()
{
	is_locked = !is_locked;
	if (is_locked) SetDfltColor(FOREGROUND_RED);
	else SetDfltColor(FOREGROUND_GREEN);
	Render();
	Sleep(100);
}

void SdkBtn::SetDigit(const uint8_t& d)
{
	digit = d;
	char new_text[2];
	new_text[0] = char(d + 48);
	new_text[1] = '\0';
	SetText(new_text);
}

uint8_t SdkBtn::GetDigit() const
{
	return digit;
}

bool SdkBtn::IsLocked() const
{
	return is_locked;
}

void SdkBtn::Click(Cursore* crsr)
{
	if (not DevModeBtn::GiveDevStatus())
	{
		if (is_locked) MessageBeep(0);
		else
		{
			if (digit + 1 > 9) SetDigit(0);
			else (SetDigit(digit + 1));
		}
	}
	else LockUp();
}

// Далее буду определять класс который нужен только для того, чтобы создавать и решать судоку

class cell
{
	bool* free_digits;
	uint8_t size;
	uint8_t digit; // 0 - нет числа
public:
	cell(const uint8_t& size, const uint8_t digit = NULL)
	{
		this->size = size;
		this->digit = digit;
		free_digits = new bool[size];
		for (uint8_t i = 0; i < size; i += 1) free_digits[i] = true; // изначально все свободны
	}

	~cell()
	{
		delete[] free_digits;
	}

	void Reset()
	{
		for (uint8_t i = 0; i < size; i += 1) free_digits[i] = true; // изначально все свободны
		digit = NULL;
	}

	uint8_t GetDigit()
	{
		return digit;
	}

	void RemoveFD(uint8_t d)
	{
		free_digits[d - 1] = false;
	}

	bool GenerateDigit()
	{
		uint8_t fd_count = 0;
		for (uint8_t i = 0; i < size; i += 1) fd_count += free_digits[i];

		if (fd_count == 0) return false;

		uint8_t tmp = rand() % fd_count;
		uint8_t true_num = 0;
		while (true)
		{
			if (free_digits[true_num])
			{
				if (tmp == 0) break;
				tmp -= 1;
			}
			true_num += 1;
		}

		digit = true_num + 1;
		free_digits[true_num] = false;
		fd_count -= 1;
		return true;
	}

	void SetDigit(uint8_t d)
	{
		digit = d;
	}
};

Sudoku::Sudoku(uint8_t open_slots_count) 
	: 
	rtrn{40,25}, 
	check{this,58,25}, 
	dev{75,25}, 
	console{"Console", 40,28},
	dev_mode{false},
	gs{this,0,25}
{
	open_slots_count %= (9*9 + 1);
	system("CLS");
	cell*** sdk = new cell**[9];
	for (uint8_t i = 0; i < 9; i += 1) sdk[i] = new cell*[9] ;
	for (uint8_t i = 0; i < 9; i += 1)
	{
		for (uint8_t j = 0; j < 9; j += 1)
		{
			sdk[i][j] = new cell{ 9 };
		}
	}

	for (uint8_t row = 0; row < 9; )
	{
		for (uint8_t line = 0; line < 9; )
		{
			for (uint8_t tl = 0; tl < line; tl += 1)
			{
				sdk[row][line]->RemoveFD(sdk[row][tl]->GetDigit());
			}
			for (uint8_t tr = 0; tr < row; tr += 1)
			{
				sdk[row][line]->RemoveFD(sdk[tr][line]->GetDigit());
			}

			for (uint8_t tr = (row / 3) * 3; tr < row; tr += 1)
			{
				for (uint8_t tl = (line / 3) * 3; tl < line; tl += 1)
				{
					sdk[row][line]->RemoveFD(sdk[tr][tl]->GetDigit());
				}
			}
			
			{
				int8_t tr = row / 3 * 3;
				int8_t tl = line / 3 * 3;
				while ((tr != row) or (tl != line))
				{
					sdk[row][line]->RemoveFD(sdk[tr][tl]->GetDigit());
					tl += 1;
					if (tl >= line / 3 * 3 + 3)
					{
						tr += 1;
						tl = line / 3 * 3;
					}
				}
			}


			if (not sdk[row][line]->GenerateDigit())
			{
				sdk[row][line]->Reset();
				if (line == 0)
				{
					row -= 1;
					line = 8;
				}
				else line -= 1;

				continue;
			}
			line += 1;
		}
		row += 1;
	}

	bool* opened = new bool[9 * 9];
	for (uint8_t i = 0; i < 9 * 9; i += 1)
	{
		opened[i] = false;
	}

	for (uint8_t i = 0; i < open_slots_count; i += 1)
	{
		uint8_t tmp = rand() % (9 * 9 - i);
		uint8_t true_num = 0;
		while (true)
		{
			if (not opened[true_num]) // здесь вс ругается, но он дбл
				// или я дбл
			{
				if (tmp == 0)
				{
					break;
				}
				tmp -= 1;
			}
			true_num += 1;
		}
		opened[true_num] = true;
	}

	table = new SdkBtn **[9];
	for (uint8_t i = 0; i < 9; i += 1) table[i] = new SdkBtn * [9];

	for (uint8_t line = 0; line < 9; line += 1)
	{
		for (uint8_t row = 0; row < 9; row += 1)
		{
			
			bool t = true;
			for (uint8_t i = 0; i < open_slots_count; i += 1)
			{
				if (opened[row + (line * 9)])
				{
					table[row][line] = new SdkBtn{ sdk[row][line]->GetDigit(), 46 + row * 4, 3 + line * 2 };
					t = false;
					break;
				}
			}
			if (t) table[row][line] = new SdkBtn{ 46 + row * 4, 3 + line * 2 };
		}
	}
	delete[] opened;

	Button::Connect(gs, rtrn, ConType::LeftRight);

	Button::Connect(rtrn, check, ConType::LeftRight);

	Button::Connect(check, dev, ConType::LeftRight);

	for (uint8_t row = 0; row < 9; row += 1)
	{
		for (uint8_t line = 0; line < 9; line += 1)
		{
			if (row+1 < 9)Button::Connect(*table[row][line], *table[row + 1][line], ConType::LeftRight);
			if (line + 1 < 9)Button::Connect(*table[row][line], *table[row][line+1], ConType::UpDown);

			delete sdk[row][line];
		}
	}
	for (uint8_t i = 0; i < 9; i += 1) delete[] sdk[i];
	delete[] sdk;

	for (uint8_t row = 0; row < 9; row += 1)
	{
		Button::Connect(*table[row][9-1], check, ConType::UpDown);
	}
	Button::Connect(*table[9/2][9 - 1], check, ConType::UpDown);
}

void Sudoku::Render() const
{
	for (uint8_t i = 0; i < 9; i++)
	{
		for (uint8_t j = 0; j < 9; j++)
		{
			table[i][j]->Render();
		}
	}
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 7);
	for (uint8_t i = 0; i < 2; i += 1)
	{
		for (uint8_t l = 0; l < 17; l += 1)
		{
			SetConsoleCursorPosition(hStdOut, { short(56 + i*12), short(3 + l)});
			std::cout << '|';
		}
		for (uint8_t l = 0; l < 33; l += 1)
		{
			SetConsoleCursorPosition(hStdOut, { short(46 + l), short(8 + i*6) });
			std::cout << '-';
		}
	}

	//SetConsoleCursorPosition(hStdOut, { short(56 + i * 12), short(8 + i * 6) });
	for (uint8_t i = 0; i < 2; i += 1)
	{
		SetConsoleCursorPosition(hStdOut, { short(56), short(8 + i * 6) });
		std::cout << '+';
		SetConsoleCursorPosition(hStdOut, { short(56 + 12), short(8 + i * 6) });
		std::cout << '+';
	}
	rtrn.Render();
	dev.Render();
	console.Render();
	check.Render();
}

BtnNode* Sudoku::GetStartNode()
{
	return rtrn.GetNodeAdress();
}

bool Sudoku::IsDevMode() const
{
	return dev_mode;
}

void Sudoku::Check()
{
	bool** lines = new bool*[9];
	bool** rows = new bool*[9];
	bool** squares = new bool* [9];
	for (uint8_t i = 0; i < 9; i+=1)
	{
		lines[i] = new bool[9];
		rows[i] = new bool[9];
		squares[i] = new bool[9];
		for (uint8_t j = 0; j < 9; j += 1)
		{
			lines[i][j] = true;
			rows[i][j] = true;
			squares[i][j] = true;
		}
	}



	bool flag = true;
	for (uint8_t line = 0; (line < 9) and flag; line += 1)
	{
		for (uint8_t row = 0; (row < 9) and flag; row += 1)
		{
			if (table[row][line]->GetDigit() == 0)
			{
				char new_text[]{ "Console: In pos _,_ u have void cell" };
				new_text[16] = char(row + 1 + 48);
				new_text[18] = char(line + 1 + 48);
				console.SetText(new_text);
				MessageBeep(0);
				flag = false;
			}
			else
			if ((lines[line][table[row][line]->GetDigit()-1]) and (rows[row][table[row][line]->GetDigit()-1]) 
				and (squares[row / 3 + line / 3 * 3][table[row][line]->GetDigit() - 1]))
			{
				lines[line][table[row][line]->GetDigit() - 1] = false;
				rows[row][table[row][line]->GetDigit() - 1] = false;
				squares[row / 3 + line / 3 * 3][table[row][line]->GetDigit() - 1] = false;
			}
			else
			{
				char new_text[]{ "Console: In pos _,_ u have wrong" };
				new_text[16] = char(row + 1 + 48);
				new_text[18] = char(line + 1 + 48);
				console.SetText(new_text);
				MessageBeep(0);
				flag = false;
			}
		}
	}
	if (flag) console.SetText("Console: U WIN!!! GOOOD JOB MAN UR THE BEST!!!!");

	for (uint8_t i = 0; i < 9; i += 1)
	{
		delete[] lines[i];
		delete[] rows[i];
	}
	delete[] lines;
	delete[] rows;
}

void Sudoku::GetSolution()
{
	gs.SetText("u dirty cheater /(0\\_/0)\\");

	cell*** sdk = new cell * *[9];
	for (uint8_t i = 0; i < 9; i += 1) sdk[i] = new cell * [9];
	for (uint8_t i = 0; i < 9; i += 1)
	{
		for (uint8_t j = 0; j < 9; j += 1)
		{
			sdk[i][j] = new cell{ 9 };
		}
	}

	for (uint8_t row = 0; row < 9; )
	{
		for (uint8_t line = 0; line < 9; )
		{

			if (table[row][line]->IsLocked())
			{
				sdk[row][line]->SetDigit(table[row][line]->GetDigit());
				line += 1;
				continue;
			}
			for (uint8_t tl = 0; tl < line; tl += 1)
			{
				sdk[row][line]->RemoveFD(sdk[row][tl]->GetDigit());
			}
			for (uint8_t tr = 0; tr < row; tr += 1)
			{
				sdk[row][line]->RemoveFD(sdk[tr][line]->GetDigit());
			}
			for (uint8_t tl = line+1; tl < 9; tl += 1)
			{
				if (table[row][tl]->IsLocked())
				{
					sdk[row][line]->RemoveFD(table[row][tl]->GetDigit());
				}
			}
			for (uint8_t tr = row+1; tr < 9; tr += 1)
			{
				if (table[tr][line]->IsLocked())
				{
					sdk[row][line]->RemoveFD(table[tr][line]->GetDigit());
				}
			}

			{
				int8_t tr = row / 3 * 3;
				int8_t tl = line / 3 * 3;
				while ((tr != row) or (tl != line))
				{
					sdk[row][line]->RemoveFD(sdk[tr][tl]->GetDigit());
					tl += 1;
					if (tl >= line / 3 * 3 + 3)
					{
						tr += 1;
						tl = line / 3 * 3;
					}
				}
			}

			if (not sdk[row][line]->GenerateDigit())
			{
				sdk[row][line]->Reset();

				if (line == 0)
				{
					row -= 1;
					line = 9 -1;
				}
				else line -= 1;

				while (table[row][line]->IsLocked())
				{

					if (line == 0)
					{
						row -= 1;
						line = 9 - 1;
					}
					else line -= 1;

				}

				continue;
			}
			line += 1;
		}
		row += 1;
	}

		for (uint8_t row = 0; row < 9; row += 1)
		{
			for (uint8_t line = 0; line < 9; line += 1)
			{
				table[row][line]->SetDigit(sdk[row][line]->GetDigit());
				delete sdk[row][line];
			}
		}
	for (uint8_t i = 0; i < 9; i += 1) delete[] sdk[i];
	delete[] sdk;

}