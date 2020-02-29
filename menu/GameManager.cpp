#include "GameManager.h"
#include "Screen.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "GameDef.h"
#include "RoomBuilder.h"

using namespace std;

// 
void GameManager::play(Player* player) {
	this->player = player;
	(*player).setPrinterMessage(std::bind(&GameLayout::print, layout, std::placeholders::_1, std::placeholders::_2));
	srand(time(NULL));
	layout.printName((*player).getName());
	createRoom();
	keyReader();
}


// reading user input
void GameManager::keyReader() {
	GameAction action = served;
	char key;
	while (action != endGame) {
		if (_kbhit()) { // 
			key = _getch(); // receiving key input
			if (key == 0) { 
				key = _getch();
				switch (key) {
				case KEY_F10:
					action = endGame;
					system("CLS");
					break;
				case KEY_F5:
					(*player).addScore(-10);
					layout.print(score,to_string((*player).getScore()));
					action = exitRoom;
					break;
				default:
					action = served;
				}
			}
			else {
				switch (key) {
				case KEY_UP:
					action = key_up;
					break;
				case KEY_DOWN:
					action = key_down;
					break;
				case KEY_LEFT:
					action = key_left;
					break;
				case KEY_RIGHT:
					action = key_right;
					break;
				default:
					action = served;
				}
			}
			runAction(action);
		}
		else
			runAction(moveEnemy);
	}
}

// escaping room and creating a new one
void GameManager::exitFromRoom()
{
	this->layout.printInfo("room change");
	Sleep(1000);
	createRoom();
	this->layout.printInfo("  ");
	Sleep(1000);
	this->layout.printInfo("");
}

// manage occuring actions
void GameManager::runAction(GameAction action)
{
	action = (*getRoom()).runAction(action);
	switch (action)
	{
	case served:
		break;
	case exitRoom:
		exitFromRoom();
		break;
	case Failed:
		break;
	default:
		break;
	}
}

GameManager::~GameManager() {
	layout.shutCursor(true);
}

void GameManager::createRoom()
{
	RoomBuilder roomBuilder(45, 15);
	roomBuilder.setScaleCount((rand() % min(max(8,(*player).getScore()), 15)) + 1);
	roomBuilder.setEnemyCount((rand() % min(max(3,(*player).getScore()), 10)) + 1);
	roomBuilder.setDoorCount(1);
	roomBuilder.setTreasureCount(rand() % 12);
	Room room = roomBuilder.build();
	room.setPlayer(player);
	room.setPrinterMessage(std::bind(&GameLayout::print, layout, std::placeholders::_1, std::placeholders::_2));
	layout.setRoom(&room);
	
	
}
