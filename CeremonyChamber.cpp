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

#include "CeremonyChamber.hpp"

CeremonyChamber::CeremonyChamber(string n) : Room(n)
{
}

void CeremonyChamber::describeRoom()
{
	cout << "Upon going through the secret passage you find yourself standing in a large, incense filled room. " << endl;
	cout << "Six cultists cloaked in dark robes are chanting around a circle of strange markings. " << endl;
	cout << "You can not believe your eyes the floor opens up and tentacles begin to emerge. " << endl;
	cout << "One of the cultist begins to yell 'Oh ancient Azathoth, it is I who has awoken you!' 'I ask that...' " << endl;
	cout << "Before he can finish his words one of the tentacles wraps around his neck and chokes him." << endl;
	cout << "The other cultist soon join him as the monstrosity cralws out from the portal." << endl;
	cout << "You are not entirely sure just what is going on, but one thing is for certain..." << endl;
	cout << "If there is any hope for humanity, you must stop the creature before he can fully emerge." << endl;
	cout << "Otherwise humanity as we know it will cease to exist." << endl;
	cout << endl;
}

char CeremonyChamber::roomMenu()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Save humanity and attempt to destroy the creature." << endl;
	cout << "2. Give up and join everyone in the afterlife." << endl;
	cout << endl;

	//input validation
	int choice = inputValidation("Enter your choice:");

	while (choice <= 0 || choice > 4)
		choice = inputValidation("The valid choices are 1-4. Please try again.");

	cout << endl;

	if (choice == 1)
	{
		return 'X';
	}
	else if (choice == 2)
	{
		cout << "A sense of hopelessness overcomes you as approach the creature and fall to your knees." << endl;
		cout << "You feel a slimy tentacle wrap around you neck. Hopefully this wont be too painful..." << endl;
		cout << endl;
		return 'Q';
	}
	
}
