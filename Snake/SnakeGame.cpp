#include "ConsoleCursore_cmds.h"
#include <cassert>
class mapClass
{
public:
	mapClass(uint8_t height, uint8_t width)
	{
		this->height = height;
		this->width = width;
		map = new char* [height];
		for (uint8_t i = 0; i < height; i++)
		{
			map[i] = new char[width];
		}
		for (uint16_t i = 0; i < height; i++)
		{
			for (uint16_t j = 0; j < width; j++)
			{
				map[i][j] = ' ';
			}
		}
		for (uint8_t i = 0; i < height; i++)
		{
			map[i][0] = '#';
			map[i][width - 1] = '#';
		}
		for (uint8_t i = 0; i < width; i++)
		{
			map[0][i] = '#';
			map[height - 1][i] = '#';
		}
	}
	~mapClass()
	{
		for (uint8_t i = 0; i < height; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}

	void print() const
	{
		system("CLS"); // clear screen
		CursorGoto(0, 0);
		for (uint8_t i = 0; i < height; i++)
		{
			for (uint8_t j = 0; j < width; j++)
			{
				std::cout << map[i][j];
			}
			std::cout << '\n';
		}
	}
	void SpawnFruit(const uint16_t& snake_size)
	{

		uint16_t number_of_free_elements = (height - 2) * (width - 2) - snake_size;
		uint16_t x = rand();
		x %= number_of_free_elements;
		for (uint8_t i = 1; (i < height) and (x != 0); i++)
		{
			for (uint8_t j = 1; (j < width) and (x != 0); j++)
			{
				if (map[i][j] == ' ')
				{
					x--;
					if (x == 0) {
						map[i][j] = '*';
						CursorGoto(j, i);
						std::cout << '*';
					}
				}
			}
		}
	}
	void SetEntity(const char& Entity, const  uint8_t& x, const  uint8_t& y)
	{
		map[y][x] = Entity;
		CursorGoto(x, y);
		std::cout << Entity;
	}
	char GiveEntity(const uint8_t& x, const  uint8_t& y) const
	{
		return map[y][x];
	}
private:
	uint8_t height;
	uint8_t width;
	char** map;
};
class Snake
{
public:
	Snake(const uint16_t& STARTsize, mapClass& map)
	{
		death_status = false;
		uint8_t STARTposX = 2;
		uint8_t STARTposY = 9;
		assert(STARTsize > 1);
		Direction = dirRight;
		size = 1;
		_first = new SnakeElement;
		_last = _first;
		_first->posX = STARTposX;
		_first->posY = STARTposY;
		map.SetEntity('#', STARTposX, STARTposY);
		for (; size < STARTsize; size++)
		{
			_first->next = new SnakeElement;
			_first = _first->next;
			_first->posX = STARTposX + size;
			_first->posY = STARTposY;
			map.SetEntity('#', STARTposX + size, STARTposY);
		}
		map.SetEntity('@', STARTposX + STARTsize - 1, STARTposY);
		_first->next = NULL;
	}
	~Snake()
	{
		SnakeElement* tempPTR = _last;
		while (tempPTR != _first)
		{
			_last = _last->next;
			delete tempPTR;
			tempPTR = _last;
		}
		delete tempPTR;
	}

	void NextAction(mapClass& map)
	{
		// вся эта махина определяет следующее положение головы змейки
		uint8_t NextX;
		uint8_t NextY;
		switch (Direction)
		{
		case dirUp:
			NextX = _first->posX;
			NextY = _first->posY - 1;
			break;
		case dirDown:
			NextX = _first->posX;
			NextY = _first->posY + 1;
			break;
		case dirLeft:
			NextX = _first->posX - 1;
			NextY = _first->posY;
			break;
		case dirRight:
			NextX = _first->posX + 1;
			NextY = _first->posY;
			break;
		}
		if ((((GetKeyState('W') < 0) or (GetKeyState('S') < 0)) and ((Direction == dirUp) or (Direction == dirDown)))
			or (((GetKeyState('A') < 0) or (GetKeyState('D') < 0)) and ((Direction == dirLeft) or (Direction == dirRight)))) {
		}
		else {
			if (GetKeyState('W') < 0) {
				Direction = dirUp;
				NextX = _first->posX;
				NextY = _first->posY - 1;
			}
			if (GetKeyState('S') < 0) {
				Direction = dirDown;
				NextX = _first->posX;
				NextY = _first->posY + 1;
			}
			if (GetKeyState('A') < 0) {
				Direction = dirLeft;
				NextX = _first->posX - 1;
				NextY = _first->posY;
			}
			if (GetKeyState('D') < 0) {
				Direction = dirRight;
				NextX = _first->posX + 1;
				NextY = _first->posY;
			}


		}
		switch (map.GiveEntity(NextX, NextY))
		{
		case ' ':
			Move(NextX, NextY, map);
			break;
		case '*':
			EatFruit(NextX, NextY, map);
			map.SpawnFruit(size);
			break;
		case '#':
			Move(NextX, NextY, map);
			Die();
			break;
		}
	}
	void Move(const uint8_t& NextX, const uint8_t& NextY, mapClass& map)
	{
		map.SetEntity(' ', _last->posX, _last->posY);
		map.SetEntity('#', _first->posX, _first->posY);
		map.SetEntity('@', NextX, NextY);
		SnakeElement* tmpPTR = _last;
		_last = _last->next;
		_first->next = tmpPTR;
		_first = tmpPTR;
		_first->next = NULL;
		_first->posX = NextX;
		_first->posY = NextY;
	}
	void EatFruit(const uint8_t& NextX, const uint8_t& NextY, mapClass& map)
	{
		map.SetEntity('#', _first->posX, _first->posY);
		map.SetEntity('@', NextX, NextY);
		size++;
		_first->next = new SnakeElement;
		_first = _first->next;
		_first->next = NULL;
		_first->posX = NextX;
		_first->posY = NextY;
	}
	void Die()
	{
		death_status = true;
	}

	bool GetDS() const
	{
		return death_status;
	}
	uint16_t GetSize() const
	{
		return size;
	}
private:


	uint16_t size;
	bool death_status;

	enum dir { dirUp, dirDown, dirRight, dirLeft };
	dir Direction;

	struct SnakeElement
	{
		SnakeElement* next;
		uint16_t posX;
		uint16_t posY;
	};
	SnakeElement* _first;
	SnakeElement* _last;
};
uint16_t SnakeGame()
{
	srand(time(0));
	mapClass MyMap(20, 100);
	Snake MySnake(3, MyMap);
	MyMap.print();
	MyMap.SpawnFruit(MySnake.GetSize());
	while (!MySnake.GetDS())
	{
		MySnake.NextAction(MyMap);
		Sleep(80);
	}
	return MySnake.GetSize() - 3;
}