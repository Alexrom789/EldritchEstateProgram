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

#ifndef GAME_HPP
#define GAME_HPP

#include "Foyer.hpp"
#include "Study.hpp"
#include "DiningRoom.hpp"
#include "Kitchen.hpp"
#include "Hallway.hpp"
#include "Basement.hpp"
#include "MasterBedRoom.hpp"
#include "GuestRoom.hpp"
#include "CeremonyChamber.hpp"
#include "Conservatory.hpp"
#include "Garden.hpp"
#include "Creature.hpp"
#include "Cultist.hpp"
#include "Azathoth.hpp"
#include <cstdlib> 
#include <ctime>   
#include <list>

using std::list;

class Game
{
private:
	//Room Pointers.

	Room* foyer;
	Room* study;
	Room* diningRoom;
	Room* kitchen;
	Room* hallway;
	Room* basement;
	Room* guestRoom;
	Room* masterBedRoom;
	Room* ceremonyChamber;
	Room* conservatory;
	Room* garden;

	//Creature Pointers.

	Creature *cultist;
	Creature *azathoth;

//Players properties
	
	Room* curLoc;       //players current location
	int sanity;        
	int health; 
	int extralife;
	int MAX_INVT_SIZE;
	list<string> inventory;   
	list<string> discard;    
	bool isDead;
	bool isInsane;
	bool hasWon;

public:
	Game();
    void play();

	//Room event functions
	void studyEvent();
	void basementEvent();
	void hallwayEvent();
	//void masterBedroomEvent();
	void CeremonialChamberEvent();

	//search room functions
	void searchFoyer();
	void searchStudy();
	void searchDiningRoom();
	void searchKitchen();
	void searchHallway();
	void searchBasement();
	void searchMasterBedRoom();
	void searchGuestRoom();
	void searchCeremonyChamber();
	void searchConservatory();
	void searchGarden();

	//inventory management functions:
     bool inInventory(string);
	 bool inDiscardPile(string);
	 void manageInvt();

	//utility funtions:
	void resetConsole();
	void pause();
	int inputValidation(string); //for imput validation
	void winScreen();
	void loseScreen();
};

#endif // !GAME_HPP

