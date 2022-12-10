#include "sudoku-gui.h"


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
}

uint8_t SdkSizeOptionBtn::GetSize()
{
	return size;
}

SdkSizeOptionBtn::SdkSizeOptionBtn(short x, short y)
	:
	Button("9", x, y)
{
}

void SdkSizeOptionBtn::Click(Cursore* crsr)
{
	size += 1;
	if (size > 9) size = 2;

	char new_text[2];
	new_text[0] = size;
	new_text[1] = '\0';
	SetText(new_text);
}




CreateSudokuBtn::CreateSudokuBtn(short x, short y)
	: 
	Button("Play!", x, y, FOREGROUND_GREEN)
{}

void CreateSudokuBtn::Click(Cursore* crsr)
{
	Application::GetAdress()->SwitchLayout(new Sudoku(OpenSlotsOptionBtn::GetCount(), SdkSizeOptionBtn::GetSize()));
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
	about_open_slots{ "Count open slots setting: " ,50,12 },
	sdk_size{ 77,14 },
	about_sdk_size{ "Sudoku size setting: ", 50,14 }
{
	Button::Connect(play, os, ConType::LeftRight);
	Button::Connect(play, ex, ConType::UpDown);
	Button::Connect(ex, sdk_size, ConType::LeftRight);
	Button::Connect(os, sdk_size, ConType::UpDown);
}

void Menu::Render() const
{
	play.Render();
	os.Render();
	ex.Render();
	about_open_slots.Render();
	sdk_size.Render();
	about_sdk_size.Render();
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
	Button("Get Solution", x, y, FOREGROUND_BLUE)
{
	this->sdk = sdk;
}

void GetSolutionBtn::Click(Cursore* crsr)
{
	sdk->GetSolution();
}

DevModeBtn::DevModeBtn(Sudoku* sdk, short x, short y)
	:
	Button("Developer Mode", x, y, FOREGROUND_BLUE)
{
	this->sdk = sdk;
}

void DevModeBtn::Click(Cursore* crsr)
{
	sdk->SwitchDevMode();
}

SdkBtn::SdkBtn(short x, short y)
	:
	Button("0", x, y, FOREGROUND_GREEN)
{
	is_locked = false;
	digit = 0;
}


void SdkBtn::LockUp()
{
	is_locked = !is_locked;
	if (is_locked) SetColor(FOREGROUND_RED);
	else SetColor(FOREGROUND_GREEN);
	Render();
}

void SdkBtn::SetDigit(const uint8_t& d)
{
	digit = d;
	char new_text[2];
	new_text[0] = char(d + 48);
	new_text[1] = '\n';
	SetText(new_text);
	Render();
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
	if (is_locked) MessageBeep(0);
	else
	{
		if (digit + 1 >= 10) SetDigit(0);
		else (SetDigit(digit + 1));
	}
}

// Далее буду определять класс который нужен только для того, чтобы создавать и решать судоку

class cell
{
	bool* free_digits; //
	uint8_t size;
	uint8_t digit; // 0 - нет числа
public:
	cell(const uint8_t& size, const uint8_t digit = NULL)
	{
		srand(time(0));
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
};

Sudoku::Sudoku(uint8_t open_slots_count, uint8_t size) 
	: 
	rtrn{0,18}, 
	check{this,0,19}, 
	dev{this,0,20}, 
	console{"Console", 20,20},
	dev_mode{false}
{
	this->size = size;
	cell*** sdk = new cell**[size];
	for (uint8_t i = 0; i < size; i += 1) sdk[i] = new cell*[size] ;
	for (uint8_t i = 0; i < size; i += 1)
	{
		for (uint8_t j = 0; j < size; j += 1)
		{
			sdk[i][j] = new cell{ size };
		}
	}

	for (uint8_t row = 0; row < size; )
	{
		for (uint8_t line = 0; line < size; )
		{
			for (uint8_t tl = 0; tl < line; tl += 1)
			{
				sdk[row][line]->RemoveFD(sdk[row][tl]->GetDigit());
			}
			for (uint8_t tr = 0; tr < row; tr += 1)
			{
				sdk[row][line]->RemoveFD(sdk[tr][line]->GetDigit());
			}

			if (not sdk[row][line]->GenerateDigit())
			{
				sdk[row][line]->Reset();
				if (line == 0)
				{
					row -= 1;
					line = 9;
				}
				else line -= 1;
				continue;
			}
			line += 1;
		}
		row += 1;
	}

	table = new SdkBtn **[size];
	for (uint8_t i = 0; i < size; i += 1) table[i] = new SdkBtn * [size];
	for (uint8_t line = 0; line < size; line += 1)
	{
		for (uint8_t row = 0; row < size; row += 1)
		{
			table[row][line] = new SdkBtn{ row * 2,line * 2 };
			table[row][line]->SetDigit(sdk[row][line]->GetDigit());
		}
	}


	for (uint8_t i = 0; i < size; i += 1)
	{
		for (uint8_t j = 0; j < size; j += 1)
		{
			delete sdk[i][j];
		}
	}
	for (uint8_t i = 0; i < size; i += 1) delete[] sdk[i];
	delete[] sdk;
}

void Sudoku::Render() const
{
	for (uint8_t i = 0; i < size; i++)
	{
		for (uint8_t j = 0; j < size; j++)
		{
			table[i][j]->Render();
		}
	}
	rtrn.Render();
	check.Render();
	dev.Render();
	console.Render();
}

BtnNode* Sudoku::GetStartNode()
{
	return rtrn.GetNodeAdress();
}

bool Sudoku::IsDevMode() const
{
	return dev_mode;
}

void Sudoku::SwitchDevMode()
{
	dev_mode = !dev_mode;
}

void Sudoku::Check()
{
	MessageBeep(0);
}

void Sudoku::GetSolution()
{
	MessageBeep(0);
}
