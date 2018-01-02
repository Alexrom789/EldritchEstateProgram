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

#include "Study.hpp"

Study::Study(string n) : Room(n)
{

}

void Study::describeRoom()
{
	if(!hasBeenHere)
	{
	cout << "You are standing in what appears to be a study. Someone must have left in a hurry as " << endl;
	cout << "there are papers scattered all over the desk, a drawer seems to be left open and some books " << endl;
	cout << "have been knocked over. You also notice a door leading out to a conservatory." << endl;
	cout << endl;
	hasBeenHere = true;
}
	else
	{
		cout << "You are back in the study." << endl;
		cout << endl;
	}
}

void Study::showImage()
{
	string imageLines = "";

	ifstream inputFile;
	string fileName = "EEStudy.txt";

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

char Study::roomMenu()
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
		return 'S';
	else if (choice == 2)
	{
		cout << "Where would you like to go?" << endl;
		cout << "1. Out into the Conservatory." << endl;
		cout << "2. Return to the Foyer." << endl;
		cout << endl;

		//input validation
		int choice = inputValidation("Enter your choice:");

		while (choice <= 0 || choice > 4)
			choice = inputValidation("The valid choices are 1 - 2. Please try again.");

		cout << endl;

		if (choice == 1)
		{
			return 'X';
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
	else
	{
		return 'Q';
	}
}
	
