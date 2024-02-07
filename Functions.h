#pragma once
// Design Game
void drawTitle();
void drawStatus(short Status, short SMode, short SIndex);
void drawMainMenu(short SIndex);
void drawLevelMenu(short SIndex);
// Launching game
void make_2DArray();
void delete_2DArray();
void initial(short SRow, short SColumn, short SNumber_Bomb);
void drawCell(short SX, short SY, short SKieu);
void drawBoard();
void randomBomb();
void produceBomb();
void handleEvent();
void win();
void lose();
void drawDescript();
void drawNotice();
void drawWarn();
void desCript();
void TextColor(int x);
void gotoxy(int x, int y);
void Time(int total_time);
void saveGame();
void loadGame();
void Score();
void saveGameScore();
void loadGameScore();
void saveGameTime();
void loadGameTime();
void Time3();
void Time4();
void Time5();
void saveGameTime4();
void loadGameTime4();
void saveGameTime5();
void loadGameTime5();