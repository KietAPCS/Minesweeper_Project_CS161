#include "Main.h";
#include "Functions.h";
#include "Console.h";

Board_Struct BStruct;
Cell_Struct** CStruct;
Cell_Struct CCStruct[25][25];

// Variable for cin.ignore
int check = 0;
// Variable for name save
std::string nameEasy;
std::string nameMedium;
std::string nameHard;
// Variable for level
int levelScore = 0;
// Variable for current time
int ctimer = 0;
int cctime = 0;
int ctimer3 = 500000;
int ctimer4 = 1000000;
int ctimer5 = 10000000;
// Variable for timer
int total_time;
// Coordinate of X and Y to draw Board
short SCoordinateX;
short SCoordinateY;
// Update CurrentPlaying 
bool BCurrentPlaying = false;
// Make 2D_Array

void make_2DArray() {

	CStruct = new Cell_Struct * [BStruct.SColumn]; // The head pointer control smaller-head-pointer at each column

	for (int i = 0; i < BStruct.SColumn; i++) {
		CStruct[i] = new Cell_Struct[BStruct.SRow]; // For each pointer of each column, create an array (new) that controls each cells in that row.
	}
}
// Delete 2D_Array
void delete_2DArray() {

	for (int i = 0; i < BStruct.SColumn; i++) {
		delete[] CStruct[i]; // Delete each cell in a row
	}

	delete[] CStruct; // Delete the head pointer
}
// Save Coordinate of Board
void SaveCoordinate() {
	SCoordinateX = ((ConsoleWidth / 2) - BStruct.SColumn);
	SCoordinateY = (((ConsoleHeight - 6) - (BStruct.SRow))/ 2 + 7);
}
// The current pointer
COORD CPointerSite;
// Whether the user use the key?
bool BUsingKey = false;
// Initialization
void initial(short SRow, short SColumn, short SNumber_Bomb) {

	BStruct.SRow = SRow;
	BStruct.SColumn = SColumn;
	BStruct.SNumber_Bomb = SNumber_Bomb;
	BStruct.SNumber_Cell_Open = 0;
	BStruct.SNumber_Flag = 0;

	make_2DArray();
	randomBomb();
	SaveCoordinate();
	CPointerSite = { 0,0 };
	BCurrentPlaying = true;
	drawBoard();
	drawStatus(1, 0, 0);
		
}
// Get the coordinate of X
short coordinateX(short SX) {
	return (SX * 2 + SCoordinateX);
}
// Get the coordinate of Y
short coordinateY(short SY) {
	return (SY + SCoordinateY);
}
// Draw Cell
void drawCell(short SX, short SY, short SKieu) {
	switch (SKieu) {
	case 0: // Empty cell - Green
		setColorCell(coordinateX(SX), coordinateY(SY), 0, 10, "  ");
		break;
	case 1: // Num 1 (Blue word). From 1 -> 8: White
		setColorCell(coordinateX(SX), coordinateY(SY), 9, 15, "1 ");
		break;
	case 2: // Green
		setColorCell(coordinateX(SX), coordinateY(SY), 2, 15, "2 ");
		break;
	case 3: // Red
		setColorCell(coordinateX(SX), coordinateY(SY), 12, 15, "3 ");
		break;
	case 4: // Strong Blue
		setColorCell(coordinateX(SX), coordinateY(SY), 1, 15, "4 ");
		break;
	case 5: // Strong red
		setColorCell(coordinateX(SX), coordinateY(SY), 4, 15, "5 ");
		break;
	case 6: // Strong CYAN
		setColorCell(coordinateX(SX), coordinateY(SY), 3, 15, "6 ");
		break;
	case 7: // Black
		setColorCell(coordinateX(SX), coordinateY(SY), 0, 15, "7 ");
		break;
	case 8: // Pink
		setColorCell(coordinateX(SX), coordinateY(SY), 13, 15, "8 ");
		break;
	case 9: // Bomb
		setColorCell(coordinateX(SX), coordinateY(SY), 0, 12, "B ");
		break;
	case 10: // 0 even
		setColorCell(coordinateX(SX), coordinateY(SY), 0, 8, "  ");
		break;
	case 11: // 0 odd
		setColorCell(coordinateX(SX), coordinateY(SY), 0, 7, "  ");
		break;
	case 12: // Follow the pointer
		setColorCell(coordinateX(SX)+1, coordinateY(SY), 0, 13, " ");
		break;
	case 13: // Set the flag
		setColorCell(coordinateX(SX), coordinateY(SY), 12, 14, "F ");
		break;
	case 14: // Wrong flag (No bomb)
		setColorCell(coordinateX(SX), coordinateY(SY), 15, 6, "Fx");
		break;
	case 15: // Right flag (Bomb exsits)
		setColorCell(coordinateX(SX), coordinateY(SY), 12, 14, "B ");
		break;
	}
}	
// Draw Board
void drawBoard() {
	for (int i = 0; i < BStruct.SRow; i++) {
		for (int j = 0; j < BStruct.SColumn; j++) {
			// Flag
			if (CStruct[i][j].BHas_Flag) {
				drawCell(j, i, 13);
			}
			// Bomb around
			else if (CStruct[i][j].SAround_Bomb) {
				drawCell(j, i, CStruct[i][j].SAround_Bomb);
			}
			// Empty cell
			else if (CStruct[i][j].BHas_Open) {
				drawCell(j, i, 0);
			}
			// Even cells
			else if ((i % 2 && j % 2) || !(i % 2 || j % 2)) {
				drawCell(j, i, 10);
			}
			// Odd cells
			else {
				drawCell(j, i, 11);
			}
			if (BUsingKey) {
				drawCell(CPointerSite.X, CPointerSite.Y, 12);
			}
		}
	}
}
// Make random Bombs
void randomBomb() {
	short SNumber_Bomb = BStruct.SNumber_Bomb;
	short SI, SJ; // SI: Row, SJ: Column we will random
	srand(time(NULL));
	while (SNumber_Bomb) {
		SI = rand() % BStruct.SRow;
		SJ = rand() % BStruct.SColumn;
		if (CStruct[SI][SJ].BHas_Bomb) {
			continue;
		}
		CStruct[SI][SJ].BHas_Bomb = true;
		SNumber_Bomb--;
	}
}
// Produce Bombs
void produceBomb() {
	for (int i = 0; i < BStruct.SRow; i++) {
		for (int j = 0; j < BStruct.SColumn; j++) {
			std::cout << CStruct[i][j].BHas_Bomb << " ";
		}
		std::cout << std::endl;
	}
}
// Hanlde Right Click - Set the Flag
void RightClick(short SX, short SY) {
	if (SPage == 3) {
		if (!CStruct[SX][SY].BHas_Open) {
			if (CStruct[SX][SY].BHas_Flag) {
				CStruct[SX][SY].BHas_Flag = false;
				BStruct.SNumber_Flag--;
			}
			else {
				CStruct[SX][SY].BHas_Flag = true;
				BStruct.SNumber_Flag++;
			}
		}
		drawBoard();
		// Update the bombs left
		if (BStruct.SNumber_Bomb - BStruct.SNumber_Flag >= 0) {
			deleteRow(4, 1);
			drawStatus(1, 0, 0);
		}
	}
}
// Count the around bombs
short countBombAround(short SX, short SY) {
	short SCnt = 0;
	for (int i = SX - 1; i <= SX + 1; i++) {
		for (int j = SY - 1; j <= SY + 1; j++) {
			// Unvalided site
			if (i < 0 || i >= BStruct.SRow || j < 0 || j >= BStruct.SColumn || (i == SX && j == SY)) {
				continue;
			}
			// Check bombs
			if (CStruct[i][j].BHas_Bomb) {
				SCnt++;
			}
		}
	}
	return SCnt;
}
// Open the cell function
void openCell(short SX, short SY) {
	if (!CStruct[SX][SY].BHas_Open && !CStruct[SX][SY].BHas_Flag) {
		CStruct[SX][SY].BHas_Open = true;
		// Bombs exist
		if (CStruct[SX][SY].BHas_Bomb) {
			lose(); // Lose
		}
		else {
			BStruct.SNumber_Cell_Open++;
			short SBombAround = countBombAround(SX, SY);
			if (SBombAround) {
				CStruct[SX][SY].SAround_Bomb = SBombAround;
			}
			// Empty cell
			else {
				// Check around cells and call recursion
				for (int i = SX - 1; i <= SX + 1; i++) {
					for (int j = SY - 1; j <= SY + 1; j++) {
						// Unvalided site
						if (i < 0 || i >= BStruct.SRow || j < 0 || j >= BStruct.SColumn || (i == SX && j == SY)) {
							continue;
						}
						// Call recursion
						openCell(i, j);
					}
				}
			}
		}
	}
}
// Analyze whether Win or Lose
static bool Compare() {
	return ((BStruct.SNumber_Cell_Open + BStruct.SNumber_Bomb) == (BStruct.SColumn * BStruct.SRow));
}
// Handle Left Click - Open the cells
void LeftClick(short SX, short SY) {
	if (SPage==3 && !CStruct[SX][SY].BHas_Open && !CStruct[SX][SY].BHas_Flag) {
		openCell(SX, SY);
		if (BCurrentPlaying) {
			drawBoard();
			if (Compare()) {
				win();
			}
		}
	}
}
/*-----------------------------------------------------------WIN AND LOSE---------------------------------------------------------*/
// Win
void win() {
	BCurrentPlaying = false;
	delete_2DArray();
	SPage = 5; SIndex = 0;
	deleteRow(4, 1);
	drawStatus(2,2,0); // Update current status to win
}
// Lose
void lose() {
	SIndex = 0;
	// Show Bombs and Flags Right or Wrong
	for (int i = 0; i < BStruct.SRow; i++) {
		for (int j = 0; j < BStruct.SColumn; j++) {
			if (CStruct[i][j].BHas_Flag) {
				if (CStruct[i][j].BHas_Bomb) {
					drawCell(j, i, 15); // Right flag (Has Bomb)
				}
				else {
					drawCell(j, i, 14); // Wrong flag
				}
			}
			else {
				// No flag
				if (CStruct[i][j].BHas_Bomb) {
					drawCell(j, i, 9); // Show bombs
				}
			}
		}
	}
	
	BCurrentPlaying = false;
	delete_2DArray(); // Delete array
	SPage = 4;
	deleteRow(4, 1);
	drawStatus(3,3,0); // Draw status Lose
}
/*-----------------------------------------------------------KEYBOARD------------------------------------------------------------*/

//Page 1: Main menu
//Page 2: Level menu
//Page 3: Page playing
//Page 4: Page lose
//Page 5: Page win
//Page 6: Save game page (while playing)
//Page 7: Information page
//Page 8: Scores Page

// Handle input from users' keyboards
static void handleKey(KEY_EVENT_RECORD key) {
	// Check whether the users enter the key DOWN 
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode) {
		// The up key
		case VK_UP:
			switch (SPage) {
			case 1: // Main menu
				if (SAll == 5) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawMainMenu(SIndex);
				}
				break;
			case 2: // Level menu
				if (SAll == 4) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawLevelMenu(SIndex);
				}
				break;
			case 3: // Page Playing
				if (BCurrentPlaying) {
					BUsingKey = true;
					CPointerSite.Y = ((CPointerSite.Y == 0) ? BStruct.SRow - 1 : CPointerSite.Y - 1);
					drawBoard();
				}
				break;
			case 4: // Lose page
				if (SAll == 2) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawStatus(3,3,SIndex);
				}
				break;
			case 5: // Win page
				if (SAll == 2) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawStatus(2,2,SIndex);
				}
				break;
			case 6: // Save Page
				if (SAll == 2) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawStatus(1, 1, SIndex);
				}
				break;
			}
			break;
		// The down key
		case VK_DOWN:
			switch (SPage) {
			case 1: // Main menu
				if (SAll == 5) {
					if (SIndex == SAll-1) {
						SIndex = 0;
					}
					else {
						SIndex += 1;
					}
					drawMainMenu(SIndex);
				}
				break;
			case 2: // Level menu
				if (SAll == 4) {
					if (SIndex == SAll-1) {
						SIndex = 0;
					}
					else {
						SIndex += 1;
					}
					drawLevelMenu(SIndex);
				}
				break;
			case 3: // Page Playing
				if (BCurrentPlaying) {
					BUsingKey = true;
					CPointerSite.Y = ((CPointerSite.Y == BStruct.SRow - 1) ? 0 : CPointerSite.Y + 1);
					drawBoard();
				}
				break;
			case 4: // Lose page
				if (SAll == 2) {
					if (SIndex == SAll - 1) {
						SIndex = 0;
					}
					else {
						SIndex += 1;
					}
					drawStatus(3,3,SIndex);
				}
				break;
			case 5: // Win page
				if (SAll == 2) {
					if (SIndex == SAll - 1) {
						SIndex = 0;
					}
					else {
						SIndex += 1;
					}
					drawStatus(2, 2, SIndex);
				}
				break;
			case 6: // Save Page
				if (SAll == 2) {
					if (SIndex == 0) {
						SIndex = SAll - 1;
					}
					else {
						SIndex -= 1;
					}
					drawStatus(1, 1, SIndex);
				}
				break;
			}
			break;
		// The left key
		case VK_LEFT:
			if (BCurrentPlaying) {
				BUsingKey = true;
				CPointerSite.X = ((CPointerSite.X == 0) ? BStruct.SColumn - 1 : CPointerSite.X - 1);
				drawBoard();
			}
			break;
		// The right key
		case VK_RIGHT:
			if (BCurrentPlaying) {
				BUsingKey = true;
				CPointerSite.X = ((CPointerSite.X == BStruct.SColumn - 1) ? 0 : CPointerSite.X + 1);
				drawBoard();
			}
			break;
		// The enter key
		case VK_RETURN:
			switch (SPage) {
			case 1: // Main menu
				// Choose level
				if (SIndex == 0) {
					SPage = 2;
					deleteRow(4, 10);
					drawLevelMenu(0);
				}
				// Continue 
				else if (SIndex == 1) {
					check++;
					loadGame();
					deleteRow(3, 30);
					SPage = 3;
					CPointerSite = { 0,0 };
					BCurrentPlaying = true;
					drawBoard();
					drawStatus(1, 0, 0);
				}
				// Scores Page
				else if (SIndex == 2) {
					loadGameScore();
					loadGameTime();
					loadGameTime4();
					loadGameTime5();
					Score();
				}
				// Information Page
				else if (SIndex == 3) {
					deleteRow(3, 30);
					desCript();
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
				break;
			case 2: // Level menu
				// Easy
				ctimer = 0;
				if (SIndex == 0) {
					levelScore = 1; check++;
					SPage = 3;
					deleteRow(4, 50);
					initial(9, 9, 10); // initial (9,9,10)
				}
				// Medium
				else if (SIndex == 1) {
					levelScore = 2; check++;
					SPage = 3;
					deleteRow(4, 50);
					initial(16, 16, 40); //initial(16,16,40)
				}
				// Hard
				else if (SIndex == 2) {
					levelScore = 3; check++;
					SPage = 3;
					deleteRow(4, 50);
					initial(24, 24, 99); //initial(24,24,99)
				}
				// Exit
				else {
					SPage = 1;
					SIndex = 0;
					deleteRow(4, 10);
					drawMainMenu(0);
				}
				break;
			case 4: // Lose page
				if (SIndex) {
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					SIndex = 0;
					drawMainMenu(0);
					drawWarn();
				}
				else {
					SPage = 3; ctimer = 0;
					deleteRow(3, ConsoleHeight - 3);
					initial(BStruct.SRow, BStruct.SColumn, BStruct.SNumber_Bomb);
				}
				break;
			case 5: // Win page
				if (SIndex) {
					SPage = 1; SIndex = 0;
					deleteRow(3, ConsoleHeight - 3);
					drawMainMenu(0);
					drawWarn();
				}
				else {
					deleteRow(3, 40);
					TextColor(11);
					if (check == 1) std::cin.ignore();
					if (levelScore == 1) {
						loadGameTime();
						if (cctime < ctimer3) {
							gotoxy(ConsoleWidth / 2 - 40, 12); printf("CONGRATULATION, YOU ACHIEVED A NEW RECORD IN THIS GAME! YOU DID A GOOD JOB !!");
							gotoxy(ConsoleWidth / 2 - 20, 14); printf("PLEASE ENTER YOUR NAME: ");
							TextColor(3);
							std::string temp;
							std::getline(std::cin, temp);
							nameEasy = temp;
							if (nameEasy != "") {
								SPage = 1; SIndex = 0;
								deleteRow(3, ConsoleHeight - 3);
								drawMainMenu(0);
								drawWarn();
							}
							saveGameTime();
						}
						else {
							gotoxy(ConsoleWidth / 2 - 35, 14); printf("SORRY TO SAY BUT YOUR SCORE DIDN'T BREAK THE RECORD, TRY ONE MORE TIME!!");
							gotoxy(ConsoleWidth / 2 - 20, 16); printf("THANK YOU FOR PLAYING, DON'T GIVING UP");
							Sleep(6000);
							SPage = 1; SIndex = 0;
							deleteRow(3, ConsoleHeight - 3);
							drawMainMenu(0);
							drawWarn();
						}
						
					}
					else if (levelScore == 2) {
						loadGameTime4();
						if (cctime < ctimer4) {
							gotoxy(ConsoleWidth / 2 - 40, 12); printf("CONGRATULATION, YOU ACHIEVED A NEW RECORD IN THIS GAME! YOU DID A GOOD JOB !!");
							gotoxy(ConsoleWidth / 2 - 20, 14); printf("PLEASE ENTER YOUR NAME: ");
							TextColor(3);
							/*if (check == 1) std::cin.ignore();*/
							std::string temp;
							std::getline(std::cin, temp);
							nameMedium = temp;
							if (nameMedium != "") {
								SPage = 1; SIndex = 0;
								deleteRow(3, ConsoleHeight - 3);
								drawMainMenu(0);
								drawWarn();
							}
							saveGameTime4();
						}
						else {
							gotoxy(ConsoleWidth / 2 - 35, 14); printf("SORRY TO SAY BUT YOUR SCORE DIDN'T BREAK THE RECORD, TRY ONE MORE TIME!!");
							gotoxy(ConsoleWidth / 2 - 20, 16); printf("THANK YOU FOR PLAYING, DON'T GIVING UP");
							Sleep(6000);
							SPage = 1; SIndex = 0;
							deleteRow(3, ConsoleHeight - 3);
							drawMainMenu(0);
							drawWarn();
						}

					}
					else if (levelScore == 3) {
						loadGameTime5();
						if (cctime < ctimer5) {
							gotoxy(ConsoleWidth / 2 - 40, 12); printf("CONGRATULATION, YOU ACHIEVED A NEW RECORD IN THIS GAME! YOU DID A GOOD JOB !!");
							gotoxy(ConsoleWidth / 2 - 20, 14); printf("PLEASE ENTER YOUR NAME: ");
							TextColor(3);
							/*if (check == 1) std::cin.ignore();*/
							std::string temp;
							std::getline(std::cin, temp);
							nameHard = temp;
							if (nameHard != "") {
								SPage = 1; SIndex = 0;
								deleteRow(3, ConsoleHeight - 3);
								drawMainMenu(0);
								drawWarn();
							}
							saveGameTime5();
						}
						else {
							gotoxy(ConsoleWidth / 2 - 35, 14); printf("SORRY TO SAY BUT YOUR SCORE DIDN'T BREAK THE RECORD, TRY ONE MORE TIME!!");
							gotoxy(ConsoleWidth / 2 - 20, 16); printf("THANK YOU FOR PLAYING, DON'T GIVING UP");
							Sleep(6000);
							SPage = 1; SIndex = 0;
							deleteRow(3, ConsoleHeight - 3);
							drawMainMenu(0);
							drawWarn();
						}

					}
					saveGameScore();
				}
				break;
			case 6: // Save game page (Press ESC while playing)
				if (SIndex) {
					saveGame();
					SPage = 1; SIndex = 0;
					deleteRow(3, ConsoleHeight - 3);
					drawMainMenu(0);
					drawWarn();
				}
				else {
					saveGame();
					SPage = 1; SIndex = 0;
					deleteRow(3, ConsoleHeight - 3);
					drawMainMenu(0);
					drawWarn();
				}
				break;
			}
			break;
		// The ESC key
		case VK_ESCAPE:
			switch (SPage) {
			case 1: // Main menu
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
				break;
			case 2: // Level menu
				SPage = 1;
				deleteRow(4, 10);
				drawMainMenu(0);
				break;
			case 3: // Playing page
				SIndex = 0;
				SPage = 6; // Page to save Name
				BCurrentPlaying = false;
				drawStatus(1, 1, 0);
				break;
			case 4: // Lose page
				SPage = 2;
				deleteRow(3, ConsoleHeight - 3);
				drawLevelMenu(0);
				break;
			case 5: // Win page
				SPage = 1; SIndex = 0;
				deleteRow(3, ConsoleHeight - 3);
				drawMainMenu(0);
				drawWarn();
			case 7: // Information Page
				SPage = 1; SIndex = 0;
				deleteRow(3, 40);
				drawMainMenu(0);
				drawWarn();
				break;
			case 8: // Scores Page
				SPage = 1; SIndex = 0;
				deleteRow(3, 40);
				drawMainMenu(0);
				drawWarn();
				break;
			}
			break;
		// Open cells (X key)
		case Left_Click:
			LeftClick(CPointerSite.Y, CPointerSite.X);
			break;
		// Set flag (Z key)
		case Right_Click:
			RightClick(CPointerSite.Y, CPointerSite.X);
			break;
		}
	}
}
// Handle keyboard from users
void handleEvent() {
	while (1) {
		DWORD DWNumberOfEvents = 0; // Save events
		DWORD DWNumberOfEventsRead = 0; // Save number of events verified

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // Input
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // Set input value for variable DWNumberOfEvents

		if (DWNumberOfEvents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents]; // Pointer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); // Put events saved on EvenBuffer

			// Read the Events
			for (DWORD i = 0; i < DWNumberOfEvents; i++) {
				// Key handle
				if (IREventBuffer[i].EventType == KEY_EVENT) {
					handleKey(IREventBuffer[i].Event.KeyEvent);
				}
				// MOUSE handle
				/* else if (IREventBuffer[i].EventType == MOUSE_EVENT) {} */
			}
		}

		if (SPage != 3) {
			total_time = clock();
		}
		if (SPage == 3) {
			Time(total_time);
		}
	}
}
// -------------------------------------------------------DESIGN------------------------------------------------------------------------------
void drawTitle() {
	short i;

	setColorCell(0,0,15,0,"------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	setColorCell((ConsoleWidth / 2) - 32, 1, 2, 0, "MineSweeper - Phan Tuan Kiet (Must Turn on All Screen before playing)\n");
	setColor(7);

	for (i = 0; i < ConsoleWidth; i++) {
		printf("%c", 45);
	}
}
// Design the status
void drawStatus(short Status, short SMode, short SIndex) {
	SIndex = SIndex;
	SAll = 2;

	setColorBGTextXY(0, 3, 15, 0, "Mapsize: %d & %d", BStruct.SRow, BStruct.SColumn);
	setColorBGTextXY(0, 4, 15, 0, "Number of bombs: %d", BStruct.SNumber_Bomb-BStruct.SNumber_Flag);

	// Draw menu Lose and Win

	if (SMode == 1) {
		std::string SMode = "  Save  ";
		setColorBGTextXY((ConsoleWidth / 2) - (SMode.length() / 2), 4, 15, ((SIndex == 0) ? 2 : 0), "  Save  ");
	}
	if (SMode == 2) {
		std::string SWin = "  Save Name  ";
		setColorBGTextXY((ConsoleWidth / 2) - (SWin.length() / 2), 4, 15, ((SIndex == 0) ? 2 : 0), "  Save Name  ");
	}
	if (SMode == 3) {
		std::string SLose = "  Play Again  ";
		setColorBGTextXY((ConsoleWidth / 2) - (SLose.length() / 2), 4, 15, ((SIndex == 0) ? 2 : 0), "  Play Again  ");
	}
	if (SMode >= 1) {
		std::string SExit = "  Exit  ";
		setColorBGTextXY((ConsoleWidth / 2) - (SExit.length() / 2), 5, 15, ((SIndex == 1) ? 2 : 0), "  Exit  ");
	}

	// Draw Status
	// Playing
	if (Status == 1) {
		setColorBGTextXY(ConsoleWidth - 16, 4, 15, 0, "Status: %s", "Playing");
		gotoxy(0, 5); std::cout << "Time: ";
	}
	// Win
	if (Status == 2) {
		setColorBGTextXY(ConsoleWidth - 16, 4, 15, 0, "Status: %s", "Win");
		gotoxy(0, 5); std::cout << "Time: ";
	}
	// Lose
	if (Status == 3) {
		setColorBGTextXY(ConsoleWidth - 16, 4, 15, 0, "Status: %s", "Lose");
		gotoxy(0, 5); std::cout << "Time: ";
	}
	std::cout << std::endl;
	short i;
	for (i = 0; i < ConsoleWidth; i++) {
		printf("%c", 45);
	}

	if (SPage == 3) {
		gotoxy(1, 15); TextColor(2); std::cout << "Z  : OPEN CELL";
		gotoxy(1, 16); TextColor(2); std::cout << "X  : SET FLAG/ UNSET FLAG";
		gotoxy(1, 17); TextColor(2); std::cout << "ESC: SAVE OR EXIT";
		gotoxy(137, 15); TextColor(2); std::cout << "UP KEY   : GO UP";
		gotoxy(137, 16); TextColor(2); std::cout << "DOWN KEY : GO DOWN";
		gotoxy(137, 17); TextColor(2); std::cout << "LEFT KEY : GO LEFT";
		gotoxy(137, 18); TextColor(2); std::cout << "RIGHT KEY: GO RIGHT";
	}
}
// Draw Main Menu
void drawMainMenu(short SIndex) {
	// Update
	SIndex = SIndex;
	SAll = 5;
	// Draw beautiful row
	for (int i = 0; i < 40; i++)
	{
		if (i % 5 == 0) {
			TextColor(9); gotoxy(55 + i, 5);     printf("%c", 220);
		}
		else if (i % 5 == 1) {
			TextColor(10);  gotoxy(55 + i, 5);     printf("%c", 220);
		}
		else if (i % 5 == 2) {
			TextColor(11);  gotoxy(55 + i, 5);   printf("%c", 220);
		}
		else if (i % 5 == 3) {
			TextColor(12);   gotoxy(55 + i, 5);    printf("%c", 220);
		}
		else if (i % 5 == 4) {
			TextColor(13);   gotoxy(55 + i, 5);    printf("%c", 220);
		}
	}
	for (int i = 0; i < 40; i++)
	{
		if (i % 5 == 0) {
			TextColor(9); gotoxy(55 + i, 13);     printf("%c", 220);
		}
		else if (i % 5 == 1) {
			TextColor(10);  gotoxy(55 + i, 13);    printf("%c", 220);
		}
		else if (i % 5 == 2) {
			TextColor(11);  gotoxy(55 + i, 13);    printf("%c", 220);
		}
		else if (i % 5 == 3) {
			TextColor(12);   gotoxy(55 + i, 13);   printf("%c", 220);
		}
		else if (i % 5 == 4) {
			TextColor(13);   gotoxy(55 + i, 13);    printf("%c", 220);
		}
	}
	// Draw Menu
	std::string STNewGame = "  New Game  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STNewGame.length() / 2)-2, 7, 15, ((SIndex == 0) ? 1 : 0), "  New Game  ");

	std::string STContinue = "  Continue  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STContinue.length() / 2) - 2, 8, 15, ((SIndex == 1) ? 1 : 0), "  Continue  ");

	std::string STScores = "  Scores  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STScores.length() / 2)-2, 9, 15, ((SIndex == 2) ? 1 : 0), "  Scores  ");

	std::string STInformation = "  Information  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STInformation.length() / 2)-2, 10, 15, ((SIndex == 3) ? 1 : 0), "  Information  ");

	std::string STExit = "  Exit  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STExit.length() / 2)-2, 11, 15, ((SIndex == 4) ? 1 : 0), "  Exit  ");
}
// Draw Level Menu
void drawLevelMenu(short SIndex) {
	// Update
	SIndex = SIndex;
	SAll = 4;

	std::string STLevel = "  CHOOSE GAME LEVEL  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STLevel.length() / 2), 4, 15, 2, "  CHOOSE GAME LEVEL  ");

	// Draw Menu
	std::string STEasy = "  EASY (9*9 AND 10 BOMBS)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STEasy.length() / 2), 7, 15, ((SIndex == 0) ? 1 : 0), "  EASY (9*9 AND 10 BOMBS)  ");

	std::string STMedium = "  MEDIUM (16*16 AND 40 BOMBS)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STMedium.length() / 2), 8, 15, ((SIndex == 1) ? 1 : 0), "  MEDIUM (16*16 AND 40 BOMBS)  ");

	std::string STHard = "  HARD (24*24 AND 99 BOMBS)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STHard.length() / 2), 9, 15, ((SIndex == 2) ? 1 : 0), "  HARD (24*24 AND 99 BOMBS)  ");

	std::string STBack = "  BACK  ";
	setColorBGTextXY((ConsoleWidth / 2) - (STBack.length() / 2)-1, 10, 15, ((SIndex == 3) ? 1 : 0), "  BACK  ");
}
// Draw Description
void drawDescript() {
	using namespace std;
	
	string SHello = "HELLO, WELCOME TO THE GAME MINESWEEPER - MADE BY PHAN TUAN KIET (23TT2-HCMUS)";
	setColorBGTextXY((ConsoleWidth / 2) - (SHello.length() / 2) - 20 , 2, 9, 0, "  HELLO, WELCOME TO THE GAME MINESWEEPER - MADE BY PHAN TUAN KIET (23TT2-HCMUS)  ");
	cout << endl;
	string SCheck = "IF YOU WANT TO PLAY THIS GAME, PLEASE TYPE YES, BUT IF YOU DON'T, THEN TYPE NO PLEASE";
	setColorBGTextXY((ConsoleWidth / 2) - (SCheck.length() / 2) -20, 3, 9, 0, "  IF YOU WANT TO PLAY THIS GAME, PLEASE TYPE YES, BUT IF YOU DON'T, THEN TYPE NO PLEASE  ");
	cout << endl;
	string SChoice = "YOU MUST OPEN FULLSCEEEN (F11) FIRST, THEN PLEASE ENTER YOUR CHOICE: ";
	setColorBGTextXY((ConsoleWidth / 2) - (SChoice.length() / 2)-22, 8, 11, 0, "  YOU MUST OPEN FULLSCEEEN (F11) FIRST, THEN PLEASE ENTER YOUR CHOICE:  ");

}
// Draw Notice
void drawNotice() {
	using namespace std;

	string SNotice = "**BEFORE PLAYING THE GAME, READ THE INSTRUCTIONS CAREFULLY PLEASE**";
	setColorBGTextXY((ConsoleWidth / 2) - (SNotice.length() / 2), 2, 12, 0, "**BEFORE PLAYING THE GAME, READ THE INSTRUCTIONS CAREFULLY PLEASE**");
	cout << endl;
	cout << endl;
	string SNum1 = "NUMBER 1: USING THE KEYBOARD TO PLAY:CLICK UP, DOWN, RIGHT, LEFT KEY TO MOVE THE POINTER,PRESS ESC TO EXIT OR SAVE";
	setColorBGTextXY((ConsoleWidth / 2) - (SNum1.length() / 2)+2, 5, 9, 0, "  NUMBER 1: USING THE KEYBOARD TO PLAY:CLICK UP,DOWN,RIGHT,LEFT KEY TO MOVE THE POINTER,PRESS ESC TO EXIT OR SAVE");
	cout << endl;
	string SNum2 = "NUMBER 2: USING Z TO OPEN THE CELL, X TO SET THE FLAG (IF A CELL IS FLAGGED, IT CANNOT BE OPENE BY THE PLAYER!";
	setColorBGTextXY((ConsoleWidth / 2) - (SNum2.length() / 2), 6, 9, 0, "  NUMBER 2: USING Z TO OPEN THE CELL, X TO SET THE FLAG (IF A CELL IS FLAGGED, IT CANNOT BE OPENED BY THE PLAYER)  ");
	cout << endl;
	string SNum3 = "NUMBER 3: Fx IS THE FLAGGED CELL BUT HAS NO BOMB, B WITH THE YELLOW BACKGROUND IS FLAGGED CELL THAT HAS BOMB";
	setColorBGTextXY((ConsoleWidth / 2) - (SNum3.length() / 2)-1, 7, 9, 0, "  NUMBER 3: FX IS THE FLAGGED CELLS BUT HAS NO BOMB, B WITH THE YELLOW BACKGROUND IS A FLAGGED CELL THAT HAS BOMB  ");
	cout << endl;
	string SNum4 = "NUMBER 4: IF YOU WANT TO GET TO THE PREVIOUS PAGE OR EXIT WHILE PLAYING, PLEASE PRESS THE KEY ESC (KEYBOARD)!";
	setColorBGTextXY((ConsoleWidth / 2) - (SNum4.length() / 2) - 1, 8, 9, 0, "  NUMBER 4: IF YOU WANT TO GET TO THE PREVIOUS PAGE OR EXIT WHILE PLAYING, PLEASE PRESSES THE KEY ESC (KEYBOARD)! ");
	cout << endl;
	cout << endl;
	string SOk = "IF YOU HAVE READ THE INSTRUCTIONS CAREFULLY (WARNING), TYPE OK AND THEN ENJOY THE GAME! THANK YOU!";
	setColorBGTextXY((ConsoleWidth / 2) - (SOk.length() / 2)-6, 9, 10, 0, "  IF YOU HAVE READ THE INSTRUCTIONS CAREFULLY (WARNING BEFORE PLAYING), TYPE OK AND THEN ENJOY THE GAME,THANK YOU! ");
	cout << endl;
	string SCheckok = "PLEASE ENTER OK: ";
	setColorBGTextXY((ConsoleWidth / 2) - (SCheckok.length() / 2)-5, 15, 14, 0, "  PLEASE ENTER OK:  ");

}
// Draw WARNING
void drawWarn() {
	using namespace std;

	string SWarn = "LAST TIME WARNING";
	setColorBGTextXY((ConsoleWidth / 2) - (SWarn.length() / 2)-5, 25, 12, 0, "**LAST TIME WARNING**");
	cout << endl;
	string SMess1 = "Sometimes, the game can't run because the computer isn't fit with the game";
	setColorBGTextXY((ConsoleWidth / 2) - (SMess1.length() / 2)-9, 26, 9, 0, "Sometimes, the game can't run because your computer isn't fit with the game and the settings  ");
	cout << endl;
	string SMess2 = "If you can't play or meet any errors during the game, plesae turn off and open it again!";
	setColorBGTextXY((ConsoleWidth / 2) - (SMess2.length() / 2)-2, 27, 9, 0, "If you can't play or meet any errors during the game, plesae turn off game and open it again ");
	string SSorry = "Sorry for any inconvenience!";
	setColorBGTextXY((ConsoleWidth / 2) - (SSorry.length() / 2)-2, 28, 12, 0, "Sorry for any inconvenience!");
	cout << endl;

}

// Draw Description

void desCript() {
	SPage = 7;
	using namespace std;

	setColorBGTextXY(0, 3, 6, 0, "---------------------------------------------------------------------INTRODUCTION---------------------------------------------------------------------------");
	cout << endl;

	setColorBGTextXY(1, 5, 3, 0, "- Hello, my name is Phan Tuan Kiet and I'm currently a freshman at The University of Science in Ho Chi Minh city, which is one of the best IT University!");
	cout << endl;
	
	setColorBGTextXY(1, 6, 3, 0, "- I'm 18 years old and currently living in Ho Chi Minh city. I love my university (HCMUS) as this university give me the inspiration to follow CS Career!");
	cout << endl;

	setColorBGTextXY(1, 7, 3, 0, "- I love Technology and Computer, they are my passions. I want to create something useful for the world, especially in terms of technology or AI field!");
	cout << endl;

	setColorBGTextXY(1, 8, 3, 0, "- But now, I'm just a freshman and don't have much experience in coding or computer science, so I create this game to make a good foundation for later life");
	cout << endl;

	setColorBGTextXY(1, 9, 3, 0, "- I hope that this game (MINESWEEPER) will give you a relaxing time and good experience while playing. If there are any errors, just turn off and restart! ");
	cout << endl;

	setColorBGTextXY(1, 10, 3, 0, "- If you want to know more about me or the journey of my self to computer science and HCMUS, just contact my through my email: drawyouryouth@gmail.com");
	cout << endl;

	setColorBGTextXY(0, 12, 6, 0, "---------------------------------------------------------------------INSTRUCTIONS---------------------------------------------------------------------------");
	cout << endl;

	setColorBGTextXY(1, 15, 11, 0, "- Press UP, DOWN, LEFT, RIGHT to move the pointer to the cells you want to open!");
	cout << endl;
	setColorBGTextXY(1, 16, 11, 0, "- Press Z to open the cells, X to set the flag, X again to remove the flag!");
	cout << endl;
	setColorBGTextXY(1, 17, 11, 0, "- If a cell is flagged, you cannot open it!");
	cout << endl;
	setColorBGTextXY(1, 18, 11, 0, "- When you lose, Fx means the cell you flagged has bomb, while B with yellow background is the flagged cell with no bomb!");
	cout << endl;
	setColorBGTextXY(1, 19, 11, 0, "- When you win, you can save name to save the highest scores (fastest time) of playing!");
	cout << endl;
	setColorBGTextXY(1, 20, 11, 0, "- If you cannot play the game or the words are messy, it may because you didn't open FULLSCREEN, exit game and restart!");
	cout << endl;
	setColorBGTextXY(1, 21, 11, 0, "- If you can't still play the game, it may because your computer isn't fit the ConsoleWidth and ConsoleHeight, I'm so sorry!");
	cout << endl;
	setColorBGTextXY(1, 22, 11, 0, "- IF YOU WANT TO GO BACK OR SAVE GAME WHILE PLAYING, PLEASE ENTER THE KEY ESC");
	cout << endl;

	setColorBGTextXY(0, 24, 6, 0, "------------------------------------------------------------------------ABOUT---------------------------------------------------------------------------");
	cout << endl;

	gotoxy(1, 25); TextColor(11); printf("- Name      :");       gotoxy(20, 25); TextColor(10); printf("PHAN TUAN KIET");
	gotoxy(1, 26); TextColor(11); printf("- Birthday  :");       gotoxy(20, 26); TextColor(10); printf("02/02/2005");
	gotoxy(1, 27); TextColor(11); printf("- Facebook  :");       gotoxy(20, 27); TextColor(10); printf("TuanKiet.tacenda");
	gotoxy(1, 28); TextColor(11); printf("- Gmail     :");       gotoxy(20, 28); TextColor(10); printf("drawyouryouth@gmail.com");
	gotoxy(1, 29); TextColor(11); printf("- Address   :");       gotoxy(20, 29); TextColor(10); printf("9 XOM CHI STREET");
	gotoxy(1, 30); TextColor(11); printf("- Schools   :");       gotoxy(20, 30); TextColor(10); printf("HCMUS - UNIVERSITY OF SCIENCE");
	gotoxy(1, 31); TextColor(11); printf("- Class     :");       gotoxy(20, 31); TextColor(10); printf("23TT2 (K23-APCS)");
	gotoxy(1, 32); TextColor(11); printf("- Hometown  :");       gotoxy(20, 32); TextColor(10); printf("Da Nang City");
	gotoxy(1, 33); TextColor(11); printf("- Occupation:");       gotoxy(20, 33); TextColor(10); printf("FRESHMAN");
	gotoxy(1, 34); TextColor(11); printf("- Hobby     :");       gotoxy(20, 34); TextColor(10); printf("CODING");

	setColorBGTextXY(14, 36, 14, 0, "*****If you want to go back to play my game, please press the key ESC! Thank you for reading my journey! Hope you play well!*****");
	cout << endl;
	SIndex = 0;
}

// Some additional functions
void TextColor(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}
void gotoxy(int x, int y)//x,y là tọa điểm x,y trên màn hình
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD a = { x, y };    SetConsoleCursorPosition(h, a);
}
void Time(int total_time)
{
	int time = (clock() - total_time + ctimer); cctime = time; time /= 1000;
	int gio, phut, giay;
	gio = time / 3600; phut = (time / 60) % 60, giay = time % 60;
	gotoxy(6, 5); TextColor(15);
	if (giay < 10 && gio < 10 && phut < 10) printf("0%d:0%d:0%d", gio, phut, giay);
	else if (giay < 10 && gio < 10) printf("0%d:%d:0%d", gio, phut, giay);
	else if (phut < 10 && gio < 10) printf("0%d:0%d:%d", gio, phut, giay);
	else if (giay < 10 && phut < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (giay < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (gio < 10) printf("0%d:%d:%d", gio, phut, giay);
	else if (phut < 10)printf("%d:0%d:%d", gio, phut, giay);
}
void Time3()
{
	int time = ctimer3; time /= 1000;
	int gio, phut, giay;
	gio = time / 3600; phut = (time / 60) % 60, giay = time % 60;

	if (giay < 10 && gio < 10 && phut < 10) printf("0%d:0%d:0%d", gio, phut, giay);
	else if (giay < 10 && gio < 10) printf("0%d:%d:0%d", gio, phut, giay);
	else if (phut < 10 && gio < 10) printf("0%d:0%d:%d", gio, phut, giay);
	else if (giay < 10 && phut < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (giay < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (gio < 10) printf("0%d:%d:%d", gio, phut, giay);
	else if (phut < 10)printf("%d:0%d:%d", gio, phut, giay);
}
void Time4()
{
	int time = ctimer4; time /= 1000;
	int gio, phut, giay;
	gio = time / 3600; phut = (time / 60) % 60, giay = time % 60;

	if (giay < 10 && gio < 10 && phut < 10) printf("0%d:0%d:0%d", gio, phut, giay);
	else if (giay < 10 && gio < 10) printf("0%d:%d:0%d", gio, phut, giay);
	else if (phut < 10 && gio < 10) printf("0%d:0%d:%d", gio, phut, giay);
	else if (giay < 10 && phut < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (giay < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (gio < 10) printf("0%d:%d:%d", gio, phut, giay);
	else if (phut < 10)printf("%d:0%d:%d", gio, phut, giay);
}
void Time5()
{
	int time = ctimer5; time /= 1000;
	int gio, phut, giay;
	gio = time / 3600; phut = (time / 60) % 60, giay = time % 60;

	if (giay < 10 && gio < 10 && phut < 10) printf("0%d:0%d:0%d", gio, phut, giay);
	else if (giay < 10 && gio < 10) printf("0%d:%d:0%d", gio, phut, giay);
	else if (phut < 10 && gio < 10) printf("0%d:0%d:%d", gio, phut, giay);
	else if (giay < 10 && phut < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (giay < 10) printf("%d:%d:0%d", gio, phut, giay);
	else if (gio < 10) printf("0%d:%d:%d", gio, phut, giay);
	else if (phut < 10)printf("%d:0%d:%d", gio, phut, giay);
}

// SAVE GAME ----------------------------------------------------------------------------------------------------------------------
void saveGame() {
	for (int i = 0; i < BStruct.SColumn; i++) {
		for (int j = 0; j < BStruct.SRow; j++) {
			CCStruct[i][j] = CStruct[i][j];
		}
	}
	std::ofstream outFile("KietGame.txt", std::ios::binary);
	if (outFile.is_open()) {
		outFile.write(reinterpret_cast<const char*>(CCStruct), sizeof(CCStruct));
		outFile.close();
	}
	else {
		// Handle error opening file
	}
	std::ofstream outFile1("KietGame1.txt", std::ios::binary);
	if (outFile1.is_open()) {
		outFile1.write(reinterpret_cast<const char*>(&BStruct), sizeof(BStruct));
		outFile1.close();
	}
	else {
		// Handle error opening file
	}
	std::ofstream outFile2("KietGame2.txt", std::ios::binary);
	if (outFile2.is_open()) {
		outFile2.write(reinterpret_cast<const char*>(&cctime), sizeof(cctime));
		outFile2.close();
	}
	else {
		// Handle error opening file
	}
	std::ofstream outFile3("KietGame3.txt", std::ios::binary);
	if (outFile3.is_open()) {
		outFile3.write(reinterpret_cast<const char*>(&levelScore), sizeof(levelScore));
		outFile3.close();
	}
	else {
		// Handle error opening file
	}
}
void loadGame() {
	std::ifstream inFile1("KietGame1.txt", std::ios::binary);
	if (inFile1.is_open()) {
		inFile1.read(reinterpret_cast<char*>(&BStruct), sizeof(BStruct));
		inFile1.close();
	}
	else {
		// Handle error opening file
	}
	std::ifstream inFile("KietGame.txt", std::ios::binary);
	if (inFile.is_open()) {
		inFile.read(reinterpret_cast<char*>(&CCStruct), sizeof(CCStruct));
		inFile.close();
	}
	else {
		// Handle error opening file
	}
	std::ifstream inFile2("KietGame2.txt", std::ios::binary);
	if (inFile2.is_open()) {
		inFile2.read(reinterpret_cast<char*>(&ctimer), sizeof(ctimer));
		inFile2.close();
	}
	else {
		// Handle error opening file
	}
	make_2DArray();
	SaveCoordinate();
	for (int i = 0; i < BStruct.SColumn; i++) {
		for (int j = 0; j < BStruct.SRow; j++) {
			CStruct[i][j] = CCStruct[i][j];
		}
	}
	std::ifstream inFile3("KietGame3.txt", std::ios::binary);
	if (inFile3.is_open()) {
		inFile3.read(reinterpret_cast<char*>(&levelScore), sizeof(levelScore));
		inFile3.close();
	}
	else {
		// Handle error opening file
	}
}
// Score ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void saveGameScore() {
	std::ofstream outFileScore("Score.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore.is_open()) {
		outFileScore << nameEasy;
		outFileScore.close();
	}
	else {
		// Handle error opening file
	}

	std::ofstream outFileScore1("Score1.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore1.is_open()) {
		outFileScore1 << nameMedium;
		outFileScore1.close();
	}
	else {
		// Handle error opening file
	}

	std::ofstream outFileScore2("Score2.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore2.is_open()) {
		outFileScore2 << nameHard;
		outFileScore2.close();
	}
	else {
		// Handle error opening file
	}
}
void loadGameScore() {
	std::ifstream inFileScore("Score.txt", std::ios::binary);
	if (inFileScore.is_open()) {

		// Read the string data
		std::getline(inFileScore, nameEasy);

		inFileScore.close();
	}
	else {
		// Handle error opening file
	}

	std::ifstream inFileScore1("Score1.txt", std::ios::binary);
	if (inFileScore1.is_open()) {

		// Read the string data
		std::getline(inFileScore1, nameMedium);

		inFileScore1.close();
	}
	else {
		// Handle error opening file
	}

	std::ifstream inFileScore2("Score2.txt", std::ios::binary);
	if (inFileScore2.is_open()) {

		// Read the string data
		std::getline(inFileScore2, nameHard);

		inFileScore2.close();
	}
	else {
		// Handle error opening file
	}
}
// Save time easy
void saveGameTime() {
	std::ofstream outFileScore3("Score3.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore3.is_open()) {
		outFileScore3 << cctime;
		outFileScore3.close();
	}
	else {
		// Handle error opening file
	}
}
void loadGameTime() {
	std::ifstream inFileScore3("Score3.txt", std::ios::binary);
	if (inFileScore3.is_open()) {

		// Read the string data
		inFileScore3 >> ctimer3;

		inFileScore3.close();
	}
	else {
		// Handle error opening file
	}
}
// Save time medium
void saveGameTime4() {
	std::ofstream outFileScore4("Score4.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore4.is_open()) {
		outFileScore4 << cctime;
		outFileScore4.close();
	}
	else {
		// Handle error opening file
	}
}
// Save time hard
void loadGameTime4() {
	std::ifstream inFileScore4("Score4.txt", std::ios::binary);
	if (inFileScore4.is_open()) {

		// Read the string data
		inFileScore4 >> ctimer4;

		inFileScore4.close();
	}
	else {
		// Handle error opening file
	}
}
void saveGameTime5() {
	std::ofstream outFileScore5("Score5.txt", std::ios::binary | std::ios::trunc);
	if (outFileScore5.is_open()) {
		outFileScore5 << cctime;
		outFileScore5.close();
	}
	else {
		// Handle error opening file
	}
}
void loadGameTime5() {
	std::ifstream inFileScore5("Score5.txt", std::ios::binary);
	if (inFileScore5.is_open()) {

		// Read the string data
		inFileScore5 >> ctimer5;

		inFileScore5.close();
	}
	else {
		// Handle error opening file
	}
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Highest Scores Page
void Score()
{
	SPage = 8;
	deleteRow(3, 30);
	gotoxy(ConsoleWidth/2-7, 3); TextColor(160); printf(" HIGHEST SCORE ");
	TextColor(0);
	for (int i = 0; i < 45; i++)
	{
		gotoxy(18 + i, 11); printf(" ");
	}
	for (int i = 0; i < 45; i++)
	{
		gotoxy(18 + i, 21); printf(" ");
	}
	gotoxy(ConsoleWidth / 2 - 5.01, 6); TextColor(158); printf("FASTEST TIME");
	gotoxy(25, 10); TextColor(11); printf("PLAYER'S NAME : ");       gotoxy(41, 10); TextColor(3); std::cout << nameEasy;
	gotoxy(25, 11); TextColor(11); printf("LEVEL         : ");       gotoxy(41, 11); TextColor(3); std::cout << "EASY";
	gotoxy(25, 12); TextColor(11); printf("TIME          : ");		 gotoxy(41, 12); TextColor(3); Time3();

	gotoxy(25, 17); TextColor(11); printf("PLAYER'S NAME : ");       gotoxy(41, 17); TextColor(3); std::cout << nameMedium;
	gotoxy(25, 18); TextColor(11); printf("LEVEL         : ");       gotoxy(41, 18); TextColor(3); std::cout << "MEDIUM";
	gotoxy(25, 19); TextColor(11); printf("TIME          : ");       gotoxy(41, 19); TextColor(3); Time4();

	gotoxy(25, 24); TextColor(11); printf("PLAYER'S NAME : ");       gotoxy(41, 24); TextColor(3); std::cout << nameHard;
	gotoxy(25, 25); TextColor(11); printf("LEVEL         : ");       gotoxy(41, 25); TextColor(3); std::cout << "HARD";
	gotoxy(25, 26); TextColor(11); printf("TIME          : ");       gotoxy(41, 26); TextColor(3); Time5();
	
	setColorBGTextXY(14, 36, 14, 0, "*****If you want to go back to play my game, please press the key ESC! Thank you for reading my journey! Hope you play well!*****");
	std::cout << std::endl;

	TextColor(0);
}
