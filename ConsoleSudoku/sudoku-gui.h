#pragma once
#include "tools-gui.h"


class Sudoku;
class Menu;

//menu

class OpenSlotsOptionBtn : public Button
{
	static uint8_t open_slots_count;
public:
	static uint8_t GetCount();

	OpenSlotsOptionBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class SdkSizeOptionBtn : public Button
{
	static uint8_t size;
public:
	static uint8_t GetSize();

	SdkSizeOptionBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class CreateSudokuBtn : public Button
{
public:
	CreateSudokuBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class ExitBtn : public Button
{
public:
	ExitBtn(short x, short y);

	void Click(Cursore* crsr) override;
};

class Menu : public Layout
{
	CreateSudokuBtn play;
	ExitBtn ex;

	OpenSlotsOptionBtn os;
	Label about_open_slots;
	SdkSizeOptionBtn sdk_size;
	Label about_sdk_size;

public:
	Menu();

	void Render() const override;
	BtnNode* GetStartNode() override;
	uint8_t GetOpenSlotsCount() const;
};

class SdkAppl : public Application
{
	Layout* CreateStartLayout() override;
public:
	SdkAppl();
};

//sdk

class CreateMenuBtn : public Button
{
public:
	CreateMenuBtn(short x, short y);

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
	uint8_t digit;
	bool is_locked;
public:
	SdkBtn(short x, short y);

	void LockUp();
	void SetDigit(const uint8_t& d);
	uint8_t GetDigit() const;
	bool IsLocked() const;
	void Click(Cursore* crsr) override;
};


class Sudoku : public Layout
{
	SdkBtn*** table; // 81 size
	CreateMenuBtn rtrn;
	CheckBtn check;
	DevModeBtn dev;

	uint8_t size;
	bool dev_mode;

	Label console;
public:
	Sudoku(uint8_t open_slots_count, uint8_t size);

	void Render() const override;
	BtnNode* GetStartNode() override;
	bool IsDevMode() const;

	void SwitchDevMode();
	void Check();
	void GetSolution();
};