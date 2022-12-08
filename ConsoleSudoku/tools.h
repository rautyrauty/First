#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>

// “ип, позвол€ющий рисовать на экране надпись
class Label
{
protected:
	char* text;
	short x;
	short y;
	WORD color;
public:

	Label(const char* string, short x, short y, WORD color = NULL);
	~Label();

	void SetText(const char* value);
	void SetColor(WORD color);
	void Render() const;
};

//  ласс кнопки, позвол€ющий нажимать на надпись и делать еЄ мигающей
class Button : public Label
{
protected:
	uint8_t flash_countdown;
	bool flash_lever;
	const WORD dflt_color;
public:
	Button(const char* string, short x, short y, WORD color = NULL);

	void ReturnDfltColor();
	void Flashes();

	virtual void Click(Cursore* crsr) = 0;
};

// св€зка, созданна€ дл€ возможности курсора перемещатьс€ по кнопкам
struct BtnNode
{
	Button* btn = nullptr;
	BtnNode* up = nullptr;
	BtnNode* down = nullptr;
	BtnNode* left = nullptr;
	BtnNode* right = nullptr;
};

class Layout
{
	bool is_rendered;
public:

	bool IsRendered() const;

	virtual void Render() = 0;
	virtual BtnNode* GetStartNode() const = 0;
};

// ѕозвол€ет пользователю перемещатьс€ по  св€зкам 
class Cursore
{
	BtnNode* crnt_nd;
public:

	Cursore(BtnNode* start_nd = nullptr);

	void SetNode(BtnNode* new_nd);
	BtnNode* GetNode() const;

	void Set(bool mode, const size_t& size);
};

// класс отвечающий за отображение макетов и обработку событий
// Ёкземпл€р данного класса в приложении может быть только один!
class Application
{
	static Application* adress;

	Layout* crnt_lt;
	Cursore crsr;

	virtual void CreateStartLayout() = 0;
public:

	static Application* GetAdress();

	Application();

	void SwitchLayout(Layout* lt);

	void ExecHandler();
};