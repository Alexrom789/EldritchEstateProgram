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

#include "Conservatory.hpp"

Conservatory::Conservatory(string n) : Room(n)
{
	doorIsUnlocked = false; //testing now
}

void Conservatory::describeRoom()
{
	if (!doorIsUnlocked) //testing
	{
		cout << "You attempt to open the door to the conservatory, only to find it locked." << endl;
		cout << "You will have to find some way to open the door if you want to pass through." << endl;
		cout << endl;
	} 
	else if (doorIsUnlocked && !hasBeenHere)
	{
		cout << "You open the door and find yourself in what was probably once a magnificient conservatory." << endl;
		cout << "A beautiful fountain and exotic plants once made this a lovely place, " << endl;
		cout << "now however there is nothing but dying flowers and an unatural aura of something wicked." << endl;
		cout << endl;
		hasBeenHere = true;
	}
	else if (doorIsUnlocked && hasBeenHere)
	{
		cout << "You are now back in the conservatory." << endl;
		cout << endl;
	}
}

char Conservatory::roomMenu()
{
		cout << "What would you like to do?" << endl;
		cout << "1. Search room." << endl;
		cout << "2. Leave room." << endl;
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
			cout << "Where would you like to go?" << endl;
			cout << "1. Continue out into the Garden." << endl;
			cout << "2. Return to the Study." << endl;
			cout << endl;

			//input validation
			int choice = inputValidation("Enter your choice:");

			while (choice <= 0 || choice > 4)
				choice = inputValidation("The valid choices are 1 - 2. Please try again.");

			cout << endl;

			if (choice == 1)
			{
				return 'U';
			}
			else if (choice == 2)
			{
				return 'L';
			}
		}
		else if (choice == 3)
		{
			return 'I';
		}
		else if (choice == 4)
		{
			return 'Q';
		}
	}



