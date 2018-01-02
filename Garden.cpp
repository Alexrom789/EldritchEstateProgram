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

#include "Garden.hpp"

Garden::Garden(string n) : Room(n)
{
}

void Garden::describeRoom()
{
	if (!hasBeenHere)
	{
	cout << "You walk out of the conservatory into the garden." << endl;
	cout << "The rain appears to have gotten heavier and is now accompanied by lightning and thunder." << endl;
	cout << "You notice a freshly dug hole and some kind of workbench next to a dimly lit shed." << endl;
	cout << endl;
	hasBeenHere = true;
}
	else
	{
		cout << "You are back in the garden" << endl;
		cout << endl;
	}
}

char Garden::roomMenu()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Search room." << endl;
	cout << "2. Return to the Conservatory." << endl;
	cout << "3. Manage Inventory." << endl;
	cout << "4. Quit Game." << endl;
	cout << endl;

	//input validation
	int choice = inputValidation("Enter your choice:");

	while (choice <= 0 || choice > 4)
		choice = inputValidation("The valid choices are 1-4. Please try again.");

	cout << endl;

	if (choice == 1)
	{
		return 'S';
	}
	else if (choice == 2)
	{
		return 'D';
	}
	else if (choice == 3)
	{
		return 'I';
	}
	else
	{
		return 'Q';
	}
}
