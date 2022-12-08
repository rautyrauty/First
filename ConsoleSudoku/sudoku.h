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

class DevModeBtn : public Button
{
	Sudoku* sdk;
public:
	DevModeBtn(Sudoku* sdk, short x, short y);

	void Click(Cursore* crsr) override;
};

class SdkBtn : public Button
{
protected:
	uint8_t num;
	bool is_locked;
	Sudoku* sdk;
public:
	SdkBtn(Sudoku* sdk, short x, short y);

	void LockUp();
	void SetNum(const uint8_t& n);
	bool IsLocked() const;
	void Click(Cursore* crsr) override;
};

class Sudoku : public Layout
{
	BtnNode table[9][9];
	CreateMenuBtn rtrn;
	CheckBtn check;

	uint8_t* opn_slts_arr;
	bool dev_mode;

	Label console;
public:
	Sudoku(uint8_t open_slots_count);

	void Render() override;
	BtnNode* GetStartNode() const override;
	bool IsDevMode() const;

	void SwitchDevMode();
	void Check();
	void GetSolution();
};

class Menu : public Layout
{

	CreateSudokuBtn play;

	BtnNode gs_nd;
	BtnNode ex_nd;

public:
	Menu();

	void Render() override;
	BtnNode* GetStartNode() const override;

	void Connect(Layout* lt);
	void GetOpenSlotsCount();
};