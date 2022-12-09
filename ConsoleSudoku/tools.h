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

	Label(const char* string, short x, short y, WORD color = 7);
	~Label();

	void SetText(const char* value);
	void SetColor(WORD color);
	void Render() const;
};

enum class ConType
{
	UpDown,
	LeftRight
};

class Button;

class Cursore;

// св€зка, созданна€ дл€ возможности курсора перемещатьс€ по кнопкам
struct BtnNode
{
	Button* btn = nullptr;
	BtnNode* up = nullptr;
	BtnNode* down = nullptr;
	BtnNode* left = nullptr;
	BtnNode* right = nullptr;
};

//  ласс кнопки, позвол€ющий нажимать на надпись и делать еЄ мигающей
class Button : public Label
{
protected:
	const WORD dflt_color;

	BtnNode nd;
public:
	Button(const char* string, short x, short y, WORD color = 7);

	static void Connect(Button& first, Button& second, ConType ct);

	void SetDfltColor();
	WORD GetDfltColor() const;


	BtnNode* GetNodeAdress();

	virtual void Click(Cursore* crsr) = 0;
};


class Layout
{
protected:
	bool is_rendered = false;
public:

	bool IsRendered() const;

	virtual void Render() = 0;
	virtual BtnNode* GetStartNode() = 0;
};

// ѕозвол€ет пользователю перемещатьс€ по  св€зкам 
class Cursore
{
	BtnNode* current;
	uint8_t blink_countdown;
	bool blink_lever;
public:

	Cursore(BtnNode* start_nd = nullptr);

	void SetNode(BtnNode* new_nd);

	enum class Dir
	{
		up,
		left,
		right,
		down
	};
	bool IsBtnExist(Dir d) const;
	void Move(Dir d);
	void Click();
	void Blink();

	void MakeInvisible();
};

// класс отвечающий за отображение макетов и обработку событий
// Ёкземпл€р данного класса в приложении может быть только один!
class Application
{
protected:
	static Application* adress;

	Layout* crnt_lt;
	Cursore crsr;

	virtual Layout* CreateStartLayout() = 0;
public:

	static Application* GetAdress();

	void SwitchLayout(Layout* lt);

	void ExecHandler();
};