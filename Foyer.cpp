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

#include "Foyer.hpp"


Foyer::Foyer(string value) : Room(value)
{
}

void Foyer::describeRoom()
{
	if (!hasBeenHere)
	{
		cout << "You are staring at a grand double-staired entryway, surrounded by antiques of all kinds." << endl;
		cout << "You hear a blood curdling scream from somewhere inside the manor and try to compose yourself. " << endl;
		cout << "You recall your purpose for coming here. Find Vincent, investigate what is happening here, then get out. " << endl;
		cout << endl;
		hasBeenHere = true;
	}
	else
	{
		cout << "You are back in the foyer." << endl;
		cout << endl;
	}
}

void Foyer::showImage()
{
	string imageLines = "";

	ifstream inputFile;
	string fileName = "EEFoyer.txt";

	inputFile.open(fileName.c_str());

	if (inputFile)
	{
		while (inputFile)
		{
			string temp;
			getline(inputFile, temp);
			temp += "\n";
			imageLines += temp;
		}
		cout << imageLines << endl;

		inputFile.close();
	}
	else
		cout << "ERROR: Image file wasn't found..." << endl;
}

char Foyer::roomMenu()
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
		//exit room options:
		cout << "Where would you like to go?" << endl;
		cout << "1. Right into the Study." << endl;
		cout << "2. Left into the Dining Room." << endl;
		cout << "3. Down into the Basement." << endl;
		cout << "4. Upstairs into the Hallway." << endl;
		cout << endl;

		//input validation
		int choice = inputValidation("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = inputValidation("The valid choices are 1 - 4. Please try again.");

		cout << endl;

		if (choice == 1)
		{
			return 'R';
		}
		else if (choice == 2)
		{
			return 'L';
		}
		else if (choice == 3)
		{
			return 'D';
		}
		else
		{
			return 'U';
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
