#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
int main()
{
	char** map = new char* [20];
	for (int i = 0; i < 20; i++)
	{
		map[i] = new char[100];
	}
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			map[i][j] = 'w';
		}
	}
	*(*(map + 1) + 0) = 's';
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			cout << map[i][j];
		}
		cout << '\n';
	}
	return 0;
}