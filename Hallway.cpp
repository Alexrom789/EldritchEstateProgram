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

#include "Hallway.hpp"

Hallway::Hallway(string n) : Room(n)
{
}

void Hallway::describeRoom()
{
	cout << "Upon climbing the Foyer staircase you find yourself in a long corridor." << endl;
	cout << endl;
}

char Hallway::roomMenu()
{
	if (!enemyDefeated)
	{
		string imageLines = "";

		ifstream inputFile;
		string fileName = "EECultist.txt";

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

		cout << "Suddenly a hooded figure comes out from one of the rooms." << endl;
		cout << "'Hey! Who are you?' 'You shouldn't be here!' he shouts." << endl;
		cout << "He then comes lunging towards you with a dagger in hand." << endl;
		cout << endl;

		cout << "What would you like to do?" << endl;
		cout << "1. Fight the insane cultist." << endl;
		cout << "2. Attempt to Flee." << endl;
		cout << "3. Manage Inventory." << endl;
		cout << "4. Quit Game." << endl;
		cout << endl;
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
			cout << "You try to get away but the cultist is too fast." << endl;
			{
				return 'X';
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
	else
	{
		string imageLines = "";

		ifstream inputFile;
		string fileName = "EEHallway.txt";

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
			cout << "1. Right into the Master Bedroom." << endl;
			cout << "2. Left into the Guest Bedroom." << endl;
			cout << "3. Back downstairs into the Foyer." << endl;
			cout << endl;

			//input validation
			int choice = inputValidation("Enter your choice:");

			while (choice <= 0 || choice > 3)
				choice = inputValidation("The valid choices are 1 - 3. Please try again.");

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
}
