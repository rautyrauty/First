#include <iostream>
#include <Windows.h>
using namespace std;

class cell
{
	bool free_digits[9]; // от 1 до 9
	uint8_t digit; // 0 - нет числа
public:
	cell()
	{
		srand(time(0));
		for (uint8_t i = 0; i < 9; i += 1) free_digits[i] = true; // изначально все свободны
		digit = NULL;
	}

	void Reset()
	{
		for (uint8_t i = 0; i < 9; i += 1) free_digits[i] = true; // изначально все свободны
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
		for (uint8_t i = 0; i < 9; i += 1) fd_count += free_digits[i];

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

void GenerateSudoku(cell sdk[9][9])
{
	for (uint8_t row = 0; row < 9; )
	{
		for (uint8_t line = 0; line < 9; )
		{
			for (uint8_t tl = 0; tl < line; tl += 1)
			{
				sdk[row][line].RemoveFD(sdk[row][tl].GetDigit());
			}
			for (uint8_t tr = 0; tr < row; tr += 1)
			{
				sdk[row][line].RemoveFD(sdk[tr][line].GetDigit());
			}
			
			{
				int8_t tr = row / 3 * 3;
				int8_t tl = line / 3 * 3;
				while ((tr != row) or (tl != line))
				{
					sdk[row][line].RemoveFD(sdk[tr][tl].GetDigit());
					tl += 1;
					if (tl >= line / 3 * 3 + 3)
					{
						tr += 1;
						tl = line / 3 * 3;
					}
				}
			}

			if (not sdk[row][line].GenerateDigit())
			{
				sdk[row][line].Reset();
				if (line == 0)
				{
					row -= 1;
					line = 8;
				}
				else line -= 1;
				continue;
			}
			cout << (int)row << ' ' << (int)line << '\n';
			line += 1;
		}
		row += 1;
	}
}

void PrintSudoku(cell sdk[9][9])
{
	for (uint8_t line = 0; line < 9; line += 1)
	{
		for (uint8_t row = 0; row < 9; row += 1)
		{
			cout << (int)sdk[row][line].GetDigit() << '\t';
		}
		cout << '\n';
	}
}



int main()
{
	cell sdk[9][9];
	GenerateSudoku(sdk);
	PrintSudoku(sdk);
	//srand(time(0));
	//bool* opened = new bool[9 * 9];
	//for (uint8_t i = 0; i < 9 * 9; i += 1)
	//{
	//	opened[i] = false;
	//}

	//for (uint8_t i = 0; i < 20; i += 1)
	//{
	//	uint8_t tmp = rand() % (9 * 9 - i);
	//	uint8_t true_num = 0;
	//	while (true)
	//	{
	//		if (not opened[true_num]) // здесь вс ругается, но он дбл
	//		{
	//			if (tmp == 0)
	//			{
	//				break;
	//			}
	//			tmp -= 1;
	//		}
	//		true_num += 1;
	//	}
	//	opened[true_num] = true;
	//}
	//int counter = 0;
	//for (int i = 0; i < 81; i += 1)
	//{
	//	cout << i << ' ' << opened[i] << '\n';
	//	if (opened[i]) counter += 1;
	//}
	//cout << counter << " Hello" << '\n';
}