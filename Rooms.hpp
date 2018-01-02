/****************************************************************************************************
** Program name: Eldritch Estate text adventure Game (CS 162 Final Project)
** Author: Alejandro Romero
** Date: 2/14/2017
** Description: This program is an H.P Lovecraft inspired horror mystery themed text adventure game.
** The goal of the game will be for the player to piece together clues to solve a mystery and stop a
** powerful creature before they go insane. (Sanity loss will be how I implement my time limit.)
** The game will take place at an estate which contains many rooms (linked pointer variables)
** to be explored. The program also makes use of containers for inventory and discard piles.
** The game is won once the final boss has been defeated, and lost if the player dies (health reached 0)
** or goes insane before they can solve the mystery. (sanity reaches 0).
******************************************************************************************************/

#ifndef ROOM_HPP
#define ROOM_HPP
#include <fstream> //testing
#include<iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline; //testing
using std::ifstream;

class Room
{
protected:
	string roomName;
	Room* right;
	Room* left;
	Room* up;
	Room* down;

	std::string name;       
	bool hasBeenHere;  //determines if player has entered room before. 
	bool doorIsUnlocked;
	bool roomLit;        
	bool enemyDefeated;

public:
	Room(string);
	virtual void describeRoom() = 0;
	virtual char roomMenu() = 0;
	virtual void showImage();
	void setDoorToUnlock(bool); 
	void setPointer(char, Room*);
	void setLightsOn(bool);
	void setEnemyDefeated(bool);
    void setHasBeenHere(bool);
	//void setHasRune(bool);

	//Room directional functions

	Room* getRight();
	Room* getLeft();
	Room* getUp();
	Room* getDown();
	string getName();
	int inputValidation(string);
};

#endif // !ROOM_HPP

