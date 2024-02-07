#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <atomic>
#include <fstream>

#define Left_Click 0x5A
#define Right_Click 0x58

#define ConsoleWidth 156
#define ConsoleHeight 35

// Page, Index and All headlines
extern short SPage;
extern short SIndex;
extern short SAll;

struct Board_Struct {
	short SRow = 0;
	short SColumn = 0;
	short SNumber_Bomb = 0;
	short SNumber_Cell_Open = 0;
	short SNumber_Flag = 0;
};
struct Cell_Struct {
	bool BHas_Bomb = false; // There is a bomb there
	bool BHas_Open = false; // Whether the cell is opened
	bool BHas_Flag = false; // Whether the cell is flagged
	short SAround_Bomb = false; // The bombs around a cell
};
