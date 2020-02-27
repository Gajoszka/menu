#include "GameLayout.h"
#include "Screen.h"
#include <string>
using namespace std;

void GameLayout::setFont() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");
	wcscpy_s(cfi.FaceName, L"Consolas");
	//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

// cursor disappearance
void GameLayout::shutCursor(bool visible) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ccur;
	ccur.dwSize = sizeof(CONSOLE_CURSOR_INFO);
	ccur.bVisible = visible;
	SetConsoleCursorInfo(hStdOut, &ccur);
}

// destructor - cursor appearance
GameLayout::~GameLayout() {
	shutCursor(true);
}

// displays current score
void GameLayout::printScore(int score) {
	statsFrame.printLine(2, "Score: " + to_string(score));
}

// displays players username
void GameLayout::printName(string name) {
	statsFrame.printLine(1, "Player: " + name);
}

// displays additional information
void GameLayout::printInfo(string value) {
	infoFrame.printLine(1, value);
}

// displays room
void GameLayout::printRoom(RoomMap roomMap) {
	room.setMap(roomMap);
	room.printInside();
}