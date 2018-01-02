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

#include "Basement.hpp"

Basement::Basement(string n) : Room(n)
{

}

void Basement::describeRoom()
{
	if (roomLit)
	{
		cout << "You are standing in the basement. " << endl;
		cout << endl;
	}
}

char Basement::roomMenu()
{
	if (!roomLit)
	{
		cout << "As you open the door to the basement you are confronted with total darkness." << endl;
		cout << "Perhaps it would be wise not to proceed any further until a light source has been found." << endl;
		cout << endl;
		cout << endl;

		cout << "What would you like to do?" << endl;
		cout << "1. Decend further into the basement without a light source." << endl;
		cout << "2. Attempt to light up the basement." << endl;
		cout << "3. Return to the Foyer." << endl;
		cout << "4. Manage Inventory." << endl;
		cout << "5. Quit Game." << endl;
		cout << endl;

		//input validation
		int choice = inputValidation("Enter your choice:");

		while (choice <= 0 || choice > 5)
			choice = inputValidation("The valid choices are 1-4. Please try again.");

		cout << endl;

		if (choice == 1)
		{ 
			cout << "You decide to proceed into the pitch black room." << endl;
			cout << "You suddenly hear a monstrous roar which does not sound "<< endl;
			cout << "like any animal you are familiar with. You lose your footing " << endl;
			cout << "as you begin to plumet down the stairs. You crash against something " << endl;
			cout << "as you fall to the ground. You decide to quickly return to the Foyer " << endl;
			cout << "so that you may address your wounds. " << endl;
                        cout << endl;
			cout << endl;
			
//wait for the user to press enter before continuing 
			string pause;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			getline(cin, pause);
			cin.clear();
			cin.ignore();
			cout << "\033[2J\033[1;1H"; //comment out for VS
			//lose health
			//lose sanity?
			return 'U';


		}
		else if (choice == 2)
		{
			return 'X';
		}
		else if (choice == 3)
		{
				return 'U';
		}
		else if (choice == 4)
		{
			return 'I';
		}
		else
			return 'Q';
	}
	else if (roomLit && doorIsUnlocked)//testing
	{
		cout << "A secret passage is now revealed. " << endl;
		cout << "You get the feeling that you are close to the end. " << endl;
		cout << endl;

		cout << "What would you like to do?" << endl;
		cout << "1. Go through the passage." << endl;
		cout << "2. Return to the Foyer." << endl;
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
			return 'D';
		}
		else if (choice == 2)
		{
			return 'U';
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
		string fileName = "EEBasement.txt";

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

		///////////////////////////////////////////////////////////////////////////////

		cout << "With the basement lit up you now notice a bizarre relief on one of the walls, " << endl;
		cout << "a large wooden trunk, and a furnace." << endl;
		cout << "The sound of chanting can be heard from somewhere nearby. " << endl;
		cout << endl;
		cout << endl;

		cout << "What would you like to do?" << endl;
		cout << "1. Search the Basement." << endl;
		cout << "2. Return to the Foyer." << endl;
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
			return 'U';
		}
		else if (choice == 3)
		{
			return 'I';
		}
		else
			return 'Q';
	}
}
