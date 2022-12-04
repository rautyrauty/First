#pragma once
#include "tools.h"

class OpenSlotsOptionBtn : public Button
{
	static uint8_t open_slots_count;
public:
	static uint8_t GiveCount();

	OpenSlotsOptionBtn(const char*& string, short x, short y, WORD color = NULL);

	uint8_t GetOpenSlots();
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

// Та хуйня ради которой я сделал статичные переменные
class CreateSudokuBtn : public Button
{
public:
	CreateSudokuBtn(const char*& string, short x, short y, WORD color = NULL);

	void Flashes() override;
	void Click(Cursore* crsr) override;
};

// Та хуйня ради которой я сделал статичные переменные
class CreateMenuBtn : public Button
{
public:
	CreateMenuBtn(const char*& string, short x, short y, WORD color = NULL);

	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class ExitBtn : public Button
{
public:
	ExitBtn(const char*& string, short x, short y, WORD color = NULL);
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class CheckBtn : public Button
{
	Sudoku* sdk;
public:
	CheckBtn(Sudoku* sdk, const char*& string, short x, short y, WORD color = NULL);
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class GetSolutionBtn : public Button
{
	Sudoku* sdk;
public:
	GetSolutionBtn(Sudoku* sdk, const char*& string, short x, short y, WORD color = NULL);
	void Flashes() override;
	void Click(Cursore* crsr) override;
};

class Sudoku : public Layout
{
	BtnNode table[9][9];
	SwitchLtBtn return_nd;
	BtnNode check_nd;

	Label console;
public:
	Sudoku(uint8_t open_slots_count);

	void Render() override;
	BtnNode* GetStartNode() const override;

	void Check();
	void GetSolution();
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