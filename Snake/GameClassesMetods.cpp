#include "ConsoleCursore_cmds.h"
#include "GameClassesHeader.h"

mapClass::mapClass(uint8_t height, uint8_t width)
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
mapClass::~mapClass()
	{
		for (uint8_t i = 0; i < height; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}

void mapClass::print() const
	{
		system("CLS"); // clear screen
		CursorGoto(Position());
		for (uint8_t i = 0; i < height; i++)
		{
			for (uint8_t j = 0; j < width; j++)
			{
				std::cout << map[i][j];
			}
			std::cout << '\n';
		}
	}
void mapClass::SpawnFruit(const uint16_t& snake_size)
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
						CursorGoto(Position(j, i));
						std::cout << '*';
					}
				}
			}
		}
	}
void mapClass::SetEntity(const char& Entity, const  Position& SetPosition)
	{
		map[SetPosition.y][SetPosition.x] = Entity;
		CursorGoto(Position(SetPosition.x, SetPosition.y));
		std::cout << Entity;
	}
char mapClass::GiveEntity(const Position& GivePosition) const
	{
		return map[GivePosition.y][GivePosition.x];
	}

Snake::Snake(const uint16_t& STARTsize, mapClass& map)
{
	death_status = false;
	Position StartPosition(2, 9);
	Direction = dirRight;
	size = 1;
	_first = new SnakeElement;
	_last = _first;
	_first->posX = StartPosition.x;
	_first->posY = StartPosition.y;
	map.SetEntity('#', StartPosition);
	for (; size < STARTsize; size++)
	{
		_first->next = new SnakeElement;
		_first = _first->next;
		_first->posX = StartPosition.x + size;
		_first->posY = StartPosition.y;
		map.SetEntity('#', Position(StartPosition.x + size, StartPosition.y));
	}
	map.SetEntity('@', Position(StartPosition.x + STARTsize - 1, StartPosition.y));
	_first->next = NULL;
}
Snake::~Snake()
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

void Snake::NextAction(mapClass& map)
{
	// вся эта махина определяет следующее положение головы змейки

	
	Position NextPosition;
	switch (Direction)
	{
	case dirUp:
		NextPosition.x = _first->posX;
		NextPosition.y = _first->posY - 1;
		break;
	case dirDown:
		NextPosition.x = _first->posX;
		NextPosition.y = _first->posY + 1;
		break;
	case dirLeft:
		NextPosition.x = _first->posX - 1;
		NextPosition.y = _first->posY;
		break;
	case dirRight:
		NextPosition.x = _first->posX + 1;
		NextPosition.y = _first->posY;
		break;
	}
	if ((((GetKeyState('W') < 0) or (GetKeyState('S') < 0)) and ((Direction == dirUp) or (Direction == dirDown)))
		or (((GetKeyState('A') < 0) or (GetKeyState('D') < 0)) and ((Direction == dirLeft) or (Direction == dirRight))))
	{
	}
	else
	if (GetKeyState('W') < 0) {
		Direction = dirUp;
		NextPosition.x = _first->posX;
		NextPosition.y = _first->posY - 1;
	}
	else
		if (GetKeyState('S') < 0) {
			Direction = dirDown;
			NextPosition.x = _first->posX;
			NextPosition.y = _first->posY + 1;
		}
		else
			if (GetKeyState('A') < 0) {
				Direction = dirLeft;
				NextPosition.x = _first->posX - 1;
				NextPosition.y = _first->posY;
			}
			else
				if (GetKeyState('D') < 0) {
					Direction = dirRight;
					NextPosition.x = _first->posX + 1;
					NextPosition.y = _first->posY;
				}
	switch (map.GiveEntity(NextPosition))
	{
	case ' ':
		Move(NextPosition, map);
		break;
	case '*':
		EatFruit(NextPosition, map);
		map.SpawnFruit(size);
		break;
	case '#':
		Move(NextPosition, map);
		Die();
		break;
	}
}
void Snake::Move(const Position& NextPosition, mapClass& map)
{
	map.SetEntity(' ', Position(_last->posX, _last->posY));
	map.SetEntity('#', Position(_first->posX, _first->posY));
	map.SetEntity('@', NextPosition);
	SnakeElement* tmpPTR = _last;
	_last = _last->next;
	_first->next = tmpPTR;
	_first = tmpPTR;
	_first->next = NULL;
	_first->posX = NextPosition.x;
	_first->posY = NextPosition.y;
}
void Snake::EatFruit(const Position& NextPosition, mapClass& map)
{
	map.SetEntity('#', Position(_first->posX, _first->posY));
	map.SetEntity('@', NextPosition);
	size++;
	_first->next = new SnakeElement;
	_first = _first->next;
	_first->next = NULL;
	_first->posX = NextPosition.x;
	_first->posY = NextPosition.y;
}
void Snake::Die()
{
	death_status = true;
}

bool Snake::GetDS() const
{
	return death_status;
}
uint16_t Snake::GetSize() const
{
	return size;
}