#include <iostream>
#include <Windows.h>
#include <conio.h>

const int height = 20;
const int width = 100;

int main()
{
	char map[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			if ((k == 0) or (i == 0) or (i == height - 1) or (k == width - 1)) map[i][k] = '#';
			else map[i][k] = ' ';
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			std::cout << map[i][k];
		}
	}
}