#pragma once
#include "tools.h"

class MenuBtn : public Button
{
protected:
	static uint8_t open_slots_setting;
public:
	MenuBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : Button(itext, ix, iy, btn_color) {}
};

class PlayBtn : public MenuBtn
{
public:
	PlayBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : MenuBtn(itext, ix, iy, btn_color) {}

	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class OpenSlotsOptionBtn : public MenuBtn
{
public:
	OpenSlotsOptionBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : MenuBtn(itext, ix, iy, btn_color) {}

	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class ExitBtn : public MenuBtn
{
public:
	ExitBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : MenuBtn(itext, ix, iy, btn_color) {}

	void Flashes() override;
	void Click(Cursore* crsr) override;
};


class Sudoku : public Layout
{
	uint8_t open_slots_count;
	uint8_t 
	Layout* menu;

	BtnNode table[9][9];
	BtnNode return_nd;
	BtnNode check_nd;
public:

	Sudoku()
	{
		for (uint8_t i = 0; i < 9; i += 1)
		{
			for (uint8_t j = 0; j < 9; j += 1)
			{
				if (i == 0) table[i][j].up = nullptr;
				else table[i][j].up = &table[i-1][j];
			}
		}
	}
	void Render() override;
	BtnNode* GetStartNode() override;
};

class Menu : public Layout
{

	BtnNode pl_nd;
	BtnNode gs_nd;
	BtnNode ex_nd;

public:
	Menu();

	void Render() override;
	BtnNode* GetStartNode() override;
};