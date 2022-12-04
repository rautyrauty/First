#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

// Тип, позволяющий рисовать на экране надпись
class Label
{
protected:
	char text[256];
	short x;
	short y;
public:
	Label(const char* itext, short ix, short iy, WORD btn_color = NULL);
	//Label(char* itext, short ix, short iy) : Label(itext, ix, iy, NULL) {			}
	~Label();
	void SwitchColor(WORD btn_color);
};

// Класс кнопки, позволяющий нажимать на надпись и делать её мигающей
class Button : public Label
{
public:
	Button(char*& itext, short ix, short iy, WORD btn_color = NULL) : Label(itext, ix, iy, btn_color) {}

	virtual void Flashes() = 0;
	virtual void Click(Cursore* crsr) = 0;
};


// связка, созданная для возможности курсора перемещаться по кнопкам
struct BtnNode
{
	Button* btn = nullptr;
	BtnNode* up = nullptr;
	BtnNode* down = nullptr;
	BtnNode* left = nullptr;
	BtnNode* right = nullptr;
};

class SwitchLtBtn : public Button
{
	Layout* lt;
public:
	SwitchLtBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : Button(itext, ix, iy, btn_color) {}

	void Flashes() override;
	void Click(Cursore* crsr) override;
};


class Layout
{
	bool is_rendered;
public:
	bool IsRendered() const
	{ 
		return is_rendered; 
	}
	virtual void Render() = 0;
	virtual BtnNode* GetStartNode() const  = 0;

	void ConnectWith(const SwitchLtBtn& btn) const;
};

// Позволяет пользователю перемещаться по  связкам 
class Cursore
{
	Layout* crnt_lt;
	BtnNode* crnt_nd;
public:
	void SetLayout(Layout* new_lt)
	{
		crnt_lt = new_lt;
	}

	void SetNode(BtnNode* new_nd)
	{
		crnt_nd = new_nd;
	}

	Cursore(Layout* start_lt, BtnNode* start_nd = nullptr)
	{ 
		crnt_lt = start_lt; 
		if (start_nd) crnt_nd = start_nd;
		else crnt_nd = start_lt->GetStartNode();
	}
	void Set(bool mode, const size_t& size);
	void ActionHandler();
};