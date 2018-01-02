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

#include "MasterBedRoom.hpp"

MasterBedRoom::MasterBedRoom(string n) : Room(n)
{

}

void MasterBedRoom::describeRoom()
{
	
   if (!hasBeenHere)
	{
		cout << "You enter the the bedroom of Mr. Giles Weston. " << endl;
		cout << "Franticaly written gibberish is etched all over the walls." << endl;
		cout << "You can barely make out a few sensible phrases." << endl;
		cout << "'Help me!'..'Make them go away'..'It approches'..'Blood for life!" << endl;
		cout << "You wonder what on Earth could have happened here." << endl;
		cout << endl;
		hasBeenHere = true;
	}
	else
	{
		cout << "You are now back in the master bedroom." << endl;
		cout << endl;
	}
	
}

void MasterBedRoom::showImage()
{
	string imageLines = "";

	ifstream inputFile;
	string fileName = "EEMasterBedroom.txt";

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

char MasterBedRoom::roomMenu()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Search room." << endl;
	cout << "2. Return to the hallway." << endl;
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
		return 'L';
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
