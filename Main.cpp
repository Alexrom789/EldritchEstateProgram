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

#include <iostream>
#include <string>
#include <fstream> 
#include "Game.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ifstream; 

int menu();

int main()
{

	bool quit = false;
	int userChoice;

	//string pause;


	cout << "Welcome to Eldritch Estate " << endl;
	cout << "             An H.P Lovecraft inspired horror text adventure game by Alejandro Romero." << endl;
	cout << endl;
	cout << endl;



	//notify user to play in full screen (for display purposes)
	cout << endl;
	cout << "For a better playthrough experience, please assure that you are in Full Screen mode."  << endl;
	cout << "It is also reccomended to listen to The Necronomicon HP Lovecraft Orchestral Horror Music on youtube while playing." << endl;
	cout << endl;

	//wait for the user to switch to full screen
	string temp;
	cout << "PRESS ENTER TO CONTINUE" << endl;
	getline(cin, temp);
	cin.clear();
	cout << "\033[2J\033[1;1H" << endl;

	while (!quit)
	{
		//diplay the title image
		string imageLines = "";
		string fileName = "EETitleMenu.txt";

		ifstream inputFile;
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

		userChoice = menu();

		if (userChoice == 1)
		{
			inputFile.open(fileName.c_str());

			if (inputFile)
			{
				while (inputFile)
				{
					string temp1;
					getline(inputFile, temp1);
					temp1 += "\n";
					imageLines += temp1;
				}
				cout << imageLines << endl;

				inputFile.close();
			}
			else
				cout << "ERROR: Image file wasn't found..." << endl;

			cout << "You stand in the pouring rain facing the estate of Mr. Giles Weston. Not to long ago you recieved a " << endl;
			cout << "phone call from your friend, detective Vincent Barnes. He said that he once again needed your expertise." << endl;
			cout << "Expertise that 'only a distinguished professor of the Miskotonic University such as yourself' could provide." << endl;
			cout << "He recieved word from Mr.Weston's butler that 'strange' and 'unnatural' things have started to occur at the " << endl;
			cout << "estate and has asked you to meet him there to further investigate. You saw Vincents car as you approched, " << endl;
			cout << "but no signs of Vincent. You decide that he probably went on ahead and armed with nothing but your satchel " << endl;
			cout << "and note book, you resolve to enter the estate. As you attempt to knock, the door creaks open on its own " << endl;
			cout << "volition and you find yourself standing in the foyer." << endl;
			cout << endl;
			
			//pause
			string pause;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			cin.ignore(); //needed
			getline(cin, pause);
			cin.clear();
			cout << "\033[2J\033[1;1H";//comment out for VS


			Game EE;
			EE.play();
		}
		else if (userChoice == 2)
		{
			cout << "\033[2J\033[1;1H";//comment out for VS
			cout << "Eldritch Estate Walkthrough" << endl;
			cout << "**WARNING: THE FOLLOWING CONTAINS SPOLERS ON HOW TO BEAT THE GAME." << endl;
			cout << "Do not read unless you are testing the game or hopelessly stuck." << endl;
			cout << endl;

				cout << "1.	Search the under the divan in the foyer to acquire the ornate dagger. " << endl;
				cout << "2.	From the foyer go directly left into the dining room, and keep going through into the kitchen." << endl;
				cout << "3.	Search the body in the kitchen to obtain the skeleton key." << endl;
				cout << "4.	Return to the foyer and go right into the study." << endl;
				cout << "5.	Search the bust for an old brass key." << endl;
				cout << "6.	Exit the study going right into the conservatory, then go out up into the garden." << endl;
				cout << "7.	Search shed for lantern and workbench for elixir of health." << endl;
				cout << "8.	Return to foyer and then go up into the hallway." << endl;
				cout << "9.	Defeat the cultist and search his body for strange rune." << endl;
				cout << "10.	Go right into master bedroom and search under bed for elder sign." << endl;
				cout << "11.	Go back out into hallway then go left into guest bedroom." << endl;
				cout << "12.	Search body in guest bedroom for revolver." << endl;
				cout << "13.	Return to foyer." << endl;
				cout << "14.	Go down into basement and attempt to light up the room." << endl;
				cout << "15.	Examine the relief on the wall and insert strange rune." << endl;
				cout << "16.	Return to room menu and go through the secret passageway." << endl;
				cout << "17.	Defeat final Boss, win the game." << endl;
				cout << "*Note* you will be required to discard unneeded items such as notebook from inventory." << endl;	
			cout << endl;

			string pause1;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			cin.ignore(); //needed
			getline(cin, pause1);
			cin.clear();
			cout << "\033[2J\033[1;1H";//comment out for VS
		}
		else if (userChoice == 3)
		{
			quit = true;
			cout << "Thank you for using this program." << endl;
		}
	

		}
		
		return 0;
	}
	

int menu()
{
	int menuchoice;

		cout << "Please select from the following menu options and press enter." << endl;
		cout << "1. Play Game." << endl;
		cout << "2. View walthrough for beating the game. (Only recommended for testing.)" << endl;
		cout << "3. Quit. " << endl;
		cin >> menuchoice;
		switch (menuchoice)
		{
		case 1:
			return 1;
			break;

		case 2:
			return 2; 
			break;

		case 3:
			return 3;
			break;

		default:
			cout << "The valid choices are 1 through 3." << endl;
			cout << "Please try again." << endl;
			cout << endl;
		}
	}

