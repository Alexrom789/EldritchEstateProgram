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

#include "Rooms.hpp"

Room::Room(string n)
{
	if (n == "Foyer")
	{
		this->roomName = n;
	}
	else if (n == "Study")
	{
		this->roomName = n;
	}
	else if (n == "Dining Room")
	{
		this->roomName = n;
	}
	else if (n == "Kitchen")
	{
		this->roomName = n;
	}
	else if (n == "Hallway")
	{
		this->roomName = n;
	}
	else if (n == "Basement")
	{
		this->roomName = n;
	}
	else if (n == "Master Bedroom")
	{
		this->roomName = n;
	}
	else if (n == "Guest Bedroom")
	{
		this->roomName = n;
	}
	else if (n == "Ceremony Chamber")
	{
		this->roomName = n;
	}

	//initialize all location pointers to NULL
	this->up = NULL;
	this->down = NULL;
	this->right = NULL;
	this->left = NULL;

}

void Room::showImage()
{
}

void Room::setDoorToUnlock(bool tOrF)
{
	doorIsUnlocked = tOrF;
}



void Room::setPointer(char dir, Room* loc)
{
	if (dir == 'R')
	{
		this->right = loc;
	}
	else if (dir == 'L')
	{
		this->left = loc;
	}
	else if (dir == 'U')
	{
		this->up = loc;
	}
	else if (dir == 'D')
	{
		this->down = loc;
	}
}
void Room::setLightsOn(bool TorF)
{
  this->roomLit = TorF; 
}
void Room::setEnemyDefeated(bool TorF)
{
	enemyDefeated = TorF;
}
void Room::setHasBeenHere(bool yON)
{
	hasBeenHere = yON;
}
/*void Room::setHasRune(bool TorF)
{
	runeAquired = TorF;
}*/
Room * Room::getRight()
{
	return right;
}
Room * Room::getLeft()
{
	return left;
}
Room * Room::getUp()
{
	return up;
}
Room * Room::getDown()
{
	return down;
}
string Room::getName()
{
	return roomName;
}

int Room::inputValidation(std::string s)
{
	int num;

	//run the desired prompt
	cout << s << endl;
	cin >> num;

	//if  value entered is not an integer, ask the user to re-try
	while (!cin)
	{
		cout << "Invalid choice. Please enter an integer value instead." << endl;
		cin.clear();  //clears the error flag on cin
		cin.ignore(); //needed.
		cin >> num;
	}

	return num;
}