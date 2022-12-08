#pragma once
#include "tools.h"

class OpenSlotsOptionBtn : public Button
{
	static uint8_t open_slots_count;
public:
	static uint8_t GetCount();

	OpenSlotsOptionBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

// Та хуйня ради которой я сделал статичные переменные
class CreateSudokuBtn : public Button
{
public:
	CreateSudokuBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

// Та хуйня ради которой я сделал статичные переменные
class CreateMenuBtn : public Button
{
public:
	CreateMenuBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class ExitBtn : public Button
{
public:
	ExitBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class CheckBtn : public Button
{
	Sudoku* sdk;
public:
	CheckBtn(Sudoku* sdk, short x, short y);
	
	void Click(Cursore* crsr) override;
};

class GetSolutionBtn : public Button
{
	Sudoku* sdk;
public:
	GetSolutionBtn(Sudoku* sdk, short x, short y);

	void Click(Cursore* crsr) override;
};

class SdkBtn : public Button
{
	uint8_t num;
public:
	void SetNum(const uint8_t& n);

	SdkBtn(short x, short y, WORD color);
};

class DynBtn : public SdkBtn
{
public:
	DynBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class FrozenBtn : public SdkBtn
{
public:
	FrozenBtn(const char*& string, short x, short y);

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