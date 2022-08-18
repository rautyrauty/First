#pragma once
#include <iostream>
class mapClass
{
public:
	mapClass(uint8_t height, uint8_t width);
	~mapClass();

	void print() const; //Распечатывает полностью карту со всеми объектами на нём
	void SpawnFruit(const uint16_t& snake_size); // Рандомно генерирует фрукт
	void SetEntity(const char& Entity, const  Position& SetPosition); // устанавливает выбранный объект на карту
	char GiveEntity(const Position& GivePosition) const; // выдает информацию об объекте, находящийся на данной позиции

private:
	uint8_t height; // высота карты
	uint8_t width; // ширина карты
	char** map; // сама карта
};

class Snake
{
public:
	Snake(const uint16_t& STARTsize, mapClass& map);
	~Snake();

	void NextAction(mapClass& map); // Определяет следующее действие змейки и вызывает её
	void Move(const Position& NextPosition, mapClass& map); // Действие - передвижение на след. позицию
	void EatFruit(const Position& NextPosition, mapClass& map);// Действие - съесть фрукт
	void Die(); // Действие - умереть

	bool GetDS() const; // Возвращает Death Status
	uint16_t GetSize() const; // Возвращает размер змейки

private:
	uint16_t size; // размер змейки
	bool death_status;

	enum dir { dirUp, dirDown, dirRight, dirLeft };
	dir Direction; // Направление взгляда змейки

	struct SnakeElement
	{
		SnakeElement* next;
		uint16_t posX;
		uint16_t posY;
	};
	SnakeElement* _first; 
	SnakeElement* _last;
};