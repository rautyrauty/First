#pragma once
#include "tools.h"

class OpenSlotsOptionBtn : public Button
{
	uint8_t open_slots_count;
public:
	OpenSlotsOptionBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : Button(itext, ix, iy, btn_color) 
	{
		open_slots_count = 3;
	}

	uint8_t GetOpenSlots();
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class ExitBtn : public Button
{
public:
	ExitBtn(char* itext, short ix, short iy, WORD btn_color = NULL) : Button(itext, ix, iy, btn_color) {}
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class CheckBtn : public Button
{
	Sudoku* sdk;
public:
	CheckBtn(Sudoku* isdk, char* itext, short ix, short iy, WORD btn_color = NULL) : Button(itext, ix, iy, btn_color) {}
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class Sudoku : public Layout
{
	Layout* menu;

	BtnNode table[9][9];
	SwitchLtBtn return_nd;
	BtnNode check_nd;
public:

	Sudoku(uint8_t open_slots_count)
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
	void Connect(Layout* lt);

	void Render() override;
	BtnNode* GetStartNode() const override;

	void Check();
	void GenerateNewSudoku();
};

class Menu : public Layout
{

	BtnNode pl_nd;

	BtnNode gs_nd;
	BtnNode ex_nd;

public:
	Menu();

	void Render() override;
	BtnNode* GetStartNode() const override;

	void Connect(Layout* lt);
	void GetOpenSlotsCount();
};