#include "Main.h";
#include "Console.h";
#include "Functions.h";

// Making Minesweeper Game - 23125062_Phan Tuan Kiet_Project
using namespace std;
// Page, Index and All headlines
short SPage;
short SIndex;
short SAll;


int main() {

	// Hide pointer
	Cursor(false);
	// Change the size of the console screen
	resizeConsole(ConsoleWidth, ConsoleHeight);
	// Set the title for the game
	SetConsoleTitle(TEXT("MineSweeper"));

	// Main structure

	drawDescript();

	string sign;
	cin >> sign;

	for (int i = 0; i < sign.size(); i++) {
		sign[i] = toupper(sign[i]);
	}

	if (sign == "YES") {
		setColor(7);

		deleteRow(2, 1);
		deleteRow(3, 1);
		deleteRow(8, 1);

		drawNotice();
		string ok;
		cin >> ok;
		for (int i = 0; i < ok.size(); i++) {
			ok[i] = toupper(ok[i]);
		}

		if (ok == "OK") {
			deleteRow(2, 15);
		
			drawWarn();

			deleteRow(2, 1);
			deleteRow(5, 1);
			deleteRow(6, 1);

			drawTitle();
			drawMainMenu(0);
			SPage = 1;
			handleEvent();
		}
		else {
			deleteRow(0, 30);
			TextColor(14);
			gotoxy(ConsoleWidth / 2 - 15, 15); printf("THANK YOU FOR PLAYING MY GAME!!");
			gotoxy(ConsoleWidth / 2 - 13, 16); printf("HOPE YOU HAVE A GOOD DAY!!");
			TextColor(12); gotoxy(80, 17); printf("#");
			TextColor(9); gotoxy(81, 17); printf("PHAN_TUAN_KIET_23TT2");
			setBackgroundColor(0);
			std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
			Sleep(2000);
			exit(0);
		}
		
	}
	else {
		deleteRow(0, 30);
		TextColor(14);
		gotoxy(ConsoleWidth / 2 - 15, 15); printf("THANK YOU FOR PLAYING MY GAME!!");
		gotoxy(ConsoleWidth / 2 - 13, 16); printf("HOPE YOU HAVE A GOOD DAY!!");
		TextColor(12); gotoxy(80, 17); printf("#");
		TextColor(9); gotoxy(81, 17); printf("PHAN_TUAN_KIET_23TT2");
		setBackgroundColor(0);
		std::cout << std::endl; std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
		Sleep(2000);
		exit(0);
	}
	
	return 0;
 }