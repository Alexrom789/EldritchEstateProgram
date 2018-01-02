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

#include "Game.hpp"

/*****************************************************************************************************
** Name: Game Constructor Function
** Description: Creates and links together all Rooms of the game.
** It also creates and initializes the stats for the Player and Creatures(enemies).
*****************************************************************************************************/
Game::Game()
{
	//declare rooms
	foyer = new Foyer("Foyer");
	study = new Study("Study");
	diningRoom = new DiningRoom("Dining Room");
	kitchen = new Kitchen("Kitchen");
	hallway = new Hallway("Hallway");
	basement = new Basement("Basement");
	masterBedRoom = new MasterBedRoom("Master Bedroom");
	guestRoom = new GuestRoom("Guest Bedroom");
	ceremonyChamber = new CeremonyChamber("Ceremony Chambers");
	conservatory = new Conservatory("Conservatory");
	garden = new Garden("Garden");

	//declare enemies(creatures)
	cultist = new Creature(6, 2, 25, "Cultist"); 
	azathoth = new Creature(8, 3, 100, "Azathoth");
	srand(time(0));

	//link rooms to point to one another.
	foyer->setPointer('R', study);
	foyer->setPointer('L', diningRoom);
	foyer->setPointer('U', hallway);
	foyer->setPointer('D', basement);
	study->setPointer('L', foyer);
	study->setPointer('R', conservatory);
	diningRoom->setPointer('R', foyer);
	diningRoom->setPointer('L', kitchen);
	kitchen->setPointer('R', diningRoom);
	basement->setPointer('U', foyer);
	basement->setPointer('D', ceremonyChamber);
	hallway->setPointer('D', foyer);
	hallway->setPointer('R', masterBedRoom);
	hallway->setPointer('L', guestRoom);
	masterBedRoom->setPointer('L', hallway);
	guestRoom->setPointer('R', hallway);
	ceremonyChamber->setPointer('U', basement);
	conservatory->setPointer('L', study);
	conservatory->setPointer('U', garden);
	garden->setPointer('D', conservatory);

	basement->setLightsOn(false); ///testing

	//initialize the players properties.
	health = 100;
	sanity = 75; 
	extralife = 0; //If you have health elixer.
	inventory.push_back("Notebook"); // USE FOR START (Real Playthrough.)
	//inventory.push_back("Lantern"); // USE FOR TESTING ONLY.
	//inventory.push_back("Strange Rune"); // USE FOR TESTING ONLY.
	//inventory.push_back("Revolver"); // USE FOR TESTING ONLY.
	//inventory.push_back("Elder Sign"); // USE FOR TESTING ONLY.
	//basement->setHasRune(true); //TESTING ONLY
	curLoc = foyer;
	MAX_INVT_SIZE = 8; 
	isDead = false;
	hasWon = false;
}
	
/*****************************************************************************************************
** Name: Game Play Function
** Description: This funtion handles all the main functions for the gameplay. It allows the players to
** interact with the rooms by searching, calling event functions, and displaying room images.
** The play loop stopes when the player either wins, dies, or goes insane.
*****************************************************************************************************/

void Game::play()
{
	char choice;

	do
	{
		resetConsole();

		//display room tag line
		curLoc->describeRoom();

		//run the room menu
		choice = curLoc->roomMenu();

		if (choice == 'R')
		{
			//move right to the next room
			curLoc = curLoc->getRight();
		}
		else if (choice == 'L')
		{
			//move left to the next room
			curLoc = curLoc->getLeft();
		}
		else if (choice == 'U')
		{
			//move upto the next room
			curLoc = curLoc->getUp();
		}
		else if (choice == 'D')
		{
			//move down to the next room
			curLoc = curLoc->getDown();
		}
		else if (choice == 'X')
		{
			//run the room's event function
			if (curLoc == study)
			{
				studyEvent();
			}
			else if (curLoc == basement)
			{
				basementEvent();
			}
			else if (curLoc == hallway)
			{
				hallwayEvent();
			}
			else if (curLoc == ceremonyChamber)
			{
				CeremonialChamberEvent();
			}
		}
			else if (choice == 'S')
			{
				//run the room's Search function
				if (curLoc == foyer)
				{
					searchFoyer();
				}
				else if (curLoc == study)
				{
					searchStudy();
				}
				else if (curLoc == diningRoom)
				{
					searchDiningRoom();
				}
				else if (curLoc == kitchen)
				{
					searchKitchen();
				}
				else if (curLoc == basement)
				{
					searchBasement();
				}
				else if (curLoc == hallway)
				{
					searchHallway();
				}
				else if (curLoc == masterBedRoom)
				{
					searchMasterBedRoom();
				}
				else if (curLoc == guestRoom)
				{
					searchGuestRoom();
				}
				else if (curLoc == ceremonyChamber)
				{
					searchCeremonyChamber();
				}
				else if (curLoc == conservatory)
				{
					searchConservatory();
				}
				else if (curLoc == garden)
					searchGarden();
			}
				else if (choice == 'I')
				{
					//manage the players inventory
					manageInvt();
				}
				

				//check if the player has died
				if (isDead)
				{
					//resetConsole();
					if (health <= 0)
					{
						cout << "An icy chill creeps down your spine as everything around you begins to " << endl;
						cout << "turn white. You have died.  " << endl;
						cout << endl;
						pause();
					}
					else if (sanity <= 0)
					{
						cout << "You have been consumed by madness." << endl;
						cout << endl;
						pause();
					}
				}

				//decriment sanity here?
				sanity--;

				//check the time
				if (sanity == 50)
				{
					resetConsole();
					cout << "You thought you just saw something out of the corner of your eyes, yet " << endl;
					cout << "there is nothing there. Something about this place just isn't right, " << endl;
					cout << "perhaps you should make haste. " << endl;
					cout << endl;
					pause();
				}
				else if (sanity == 30)
				{
					resetConsole();
					cout << "You begin to hear voices in your head. Are you losing your mind?" << endl;
					cout << "You best figure out what's going on and get out as soon as possible." << endl;
					cout << endl;
					pause();
				}
				else if (sanity == 0)
				{
					resetConsole();
					cout << "Who are you? What are you doing in here? Why are the walls closing in?" << endl;
					cout << "All of the sudden the ground seems to open as shadowy hands reach out to pull you in." << endl;
					cout << "You curl up in the fetal position as the voices grow louder and the hands draw closer..." << endl;
					cout << endl;
					
					isDead = true;
					pause();
				}

			}
			while (choice != 'Q' && !isDead && !hasWon);

			//display the win or lose screen depending on the outcome
			if (hasWon)
			{
				winScreen();
				
			}
			else
			{
				loseScreen();
			}

			//deallocate memory here.
			delete foyer;
			delete study;
			delete diningRoom;
			delete kitchen;
			delete hallway;
			delete basement;
			delete masterBedRoom;
			delete guestRoom;
			delete ceremonyChamber;
			delete conservatory;
			delete garden;
			delete cultist; //testing
			delete azathoth;
	}

	/*****************************************************************************************************
	** Name: Study Event Function
	** Description: Handles the study special event which does not allow users to enter conservatory until
	** The Skeleton Key has been found/aquired.
	*****************************************************************************************************/
	void Game::studyEvent()
	{
		if (inInventory("Skeleton Key"))
		{
			cout << "You use the skeleton key to unlock the door." << endl;
			conservatory->setDoorToUnlock(true);
			curLoc = curLoc->getRight();
		}
		else
		{
			conservatory->setDoorToUnlock(false);
			cout << "You attempt to open the door to the conservatory, only to find it locked." << endl;
			cout << "You will have to find some way to open the door if you want to pass through." << endl;
			cout << endl;
			pause();
		}

	}

/*****************************************************************************************************
** Name: Basement Event Function
** Description: Handles the basement special event which does not allow users fully interact with basement
** until the lantern has been found/aquired. 	
*****************************************************************************************************/
	void Game::basementEvent()
	{
		if (inInventory("Lantern") && inInventory("Strange Rune"))
		{
			cout << "You use your Lantern to light up the basement." << endl;
			cout << "The strange rune begins to heat up as it pulsates faster." << endl;
			cout << endl;
			basement->setLightsOn(true);
			inventory.remove("Lantern"); 
			discard.push_back("Lantern");
			pause();
		}
		else if (inInventory("Lantern") && !inInventory("Strange Rune"))
		{
		
			cout << "You use your Lantern to light up the basement by hanging it on a post." << endl;
			cout << endl;
			basement->setLightsOn(true);
			inventory.remove("Lantern"); 
			discard.push_back("Lantern");
			pause();
		}
		else
		{
			cout << "You do not have any sources of light in your inventory." << endl;
			cout << endl;
			pause();
		}
	}

/*****************************************************************************************************
** Name: Hallway Event Function
** Description: Handles the Hallway special event which deals with combat and controls how interaction with
** the room changes depending on the status of the enemy cultist.
*****************************************************************************************************/
	void Game::hallwayEvent()
	{
		if (inInventory("Ornate Dagger") && inInventory("Health Elixer"))
		{
			cout << "With a dagger in one hand and a health elixer in the other, you feel prepared to take on your enemy." << endl;
			while (cultist->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "The cultist is attacking!" << endl;
				enemyDmgDone = cultist->rollToAtk();
				cout << "The cultist does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 12 + 2;
				cout << "You attack the cultist for " << playersDmg << " points of damage." << endl;
				cultist->setHP(cultist->getHP() - playersDmg);
				cout << "The cultist now has " << cultist->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (cultist->getHP() <= 0)
			{
				cout << "You have defeated the cultist!" << endl;
				hallway->setEnemyDefeated(true);
				cout << endl;
				pause();
			}
			if (health <= 0 && extralife == 1)
			{
				extralife--;
				cout << "You gasp for breath as the cultist knocks you down." << endl;
				cout << "You quickly chug the elixer while you have the chance." << endl;
				cout << "A sense of renewed energy uplifts you." << endl;
				health = 50;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "You have been bested by the cultist.." << endl;
				isDead = true;
				pause();
				
			}
		}
		else if (inInventory("Health Elixer") && !inInventory("Ornate Dagger"))
		{
			cout << "Armed with nothing but your fist and a health elixer, you attempt to take down the cultist." << endl;
			while (cultist->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "The cultist is attacking!" << endl;
				enemyDmgDone = cultist->rollToAtk();
				cout << "The cultist does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 6 + 1;
				cout << "You attack the cultist for " << playersDmg << " points of damage." << endl;
				cultist->setHP(cultist->getHP() - playersDmg);
				cout << "The cultist now has " << cultist->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (cultist->getHP() <= 0)
			{
				cout << "You have defeated the cultist!" << endl;
				hallway->setEnemyDefeated(true);
				cout << endl;
				pause();
			}
			if (health <= 0 && extralife == 1)
			{
				extralife--;
				cout << "You gasp for breath as the cultist knocks you down." << endl;
				cout << "You quickly chug the elixer while you have the chance." << endl;
				cout << "A sense of renewed energy uplifts you." << endl;
				health = 50;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "You have been bested by the cultist.." << endl;
				isDead = true; 
				pause();
			}
		}
		else if (inInventory("Ornate Dagger") && !inInventory("Health Elixer"))
		{
			cout << "You hold your dagger steady as you prepare to take on your foe." << endl;
			while (cultist->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "The cultist is attacking!" << endl;
				enemyDmgDone = cultist->rollToAtk();
				cout << "The cultist does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 12 + 2;
				cout << "You attack the cultist for " << playersDmg << " points of damage." << endl;
				cultist->setHP(cultist->getHP() - playersDmg);
				cout << "The cultist now has " << cultist->getHP() << " health points."<< endl;
				cout << endl;
				pause();
			}
			if (cultist->getHP() <= 0)
			{
				cout << "You have defeated the cultist!" << endl;
				hallway->setEnemyDefeated(true);
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "The cultist has bested you..." << endl;
				isDead = true; 
				cout << endl;
				pause();
			}
		}
		else
		{
			cout << "Armed with nothing but your fist, you attempt to take down the cultist." << endl;
			while (cultist->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "The cultist is attacking!" << endl;
				enemyDmgDone = cultist->rollToAtk();
				cout << "The cultist does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 6 + 1;
				cout << "You attack the cultist for " << playersDmg << " points of damage." << endl;
				cultist->setHP(cultist->getHP() - playersDmg);
				cout << "The cultist now has " << cultist->getHP() << " health points."<< endl;
				cout << endl;
				pause();
			}
			if (cultist->getHP() <= 0)
			{
				cout << "You have defeated the cultist!" << endl;
				hallway->setEnemyDefeated(true);
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "The cultist has bested you..." << endl;
				cout << endl;
				isDead = true; 
				pause();
			}
		}
	}

/*****************************************************************************************************
** Name: Ceremonial Chambers Event Function
** Description: Handles the ceremonial chambers special event which deals with combat and controls how 
** interaction with the room changes depending on the status of the enemy Boss Azathoth.
*****************************************************************************************************/
	void Game::CeremonialChamberEvent()
	{
		string imageLines = "";

		ifstream inputFile;
		string fileName = "EEAzathoth.txt";

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
		if (inInventory("Elder Sign"))
		{
			cout << "The Elder Sign beckons to you. You hold it out towards the creature as if you already know the results." << endl;
			cout << "In an unfamilar alien tongue the creature seems to cry out in pain when it attempts to lash out at you." << endl;
			cout << "The elder sign has created some kind of ward around you, weakening the enemy." << endl;
			cout << endl;
			// set Azathoth's attack die value to lower number.
			azathoth->setDVal(4);
		}
		if (inInventory("Revolver"))
		{
			cout << "You grab the Revolver and take Aim, hoping that there are still some rounds left." << endl;
			cout << "BANG!,BANG!,BANG!,BANG!,BANG!, CLICK,CLICK.  At least you got 5 shots." << endl;
			cout << "An anamolous green ooze seeps through the holes in the tentacles." << endl;
			cout << endl;
			azathoth->setHP(50);
		}
		if (inInventory("Ornate Dagger") && inInventory("Health Elixer"))
		{
			cout << "With a dagger in one hand and a health elixer in the other, you feel prepared to take on your enemy." << endl;
			while (azathoth->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "Azathoth is attacking!" << endl;
				enemyDmgDone = azathoth->rollToAtk();
				cout << "Azathoth does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 12 + 2;
				cout << "You attack Azathoth for " << playersDmg << " points of damage." << endl;
				azathoth->setHP(azathoth->getHP() - playersDmg);
				cout << "Azathoth now has " << azathoth->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (azathoth->getHP() <= 0)
			{
				cout << "You have defeated Azathoth!" << endl;
				ceremonyChamber->setEnemyDefeated(true);
				hasWon = true;
				cout << endl;
				pause();
			}
			if (health <= 0 && extralife == 1)
			{
				extralife--;
				cout << "You gasp for breath as one of Azathoth's tentacles knock you down." << endl;
				cout << "You quickly chug the elixer while you have the chance." << endl;
				cout << "A sense of renewed energy uplifts you." << endl;
				health = 50;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "You have defeated by Azathoth.." << endl;
				isDead = true; 
				pause();

			}
		}
		else if (inInventory("Health Elixer") && !inInventory("Ornate Dagger"))
		{
			cout << "Armed with nothing but your fist and a health elixer, you attempt to take down the cultist." << endl;
			while (azathoth->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "Azathoth is attacking!" << endl;
				enemyDmgDone = azathoth->rollToAtk();
				cout << "Azathoth does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 6 + 1;
				cout << "You attack Azathoth for " << playersDmg << " points of damage." << endl;
				azathoth->setHP(azathoth->getHP() - playersDmg);
				cout << "Azathoth now has " << azathoth->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (azathoth->getHP() <= 0)
			{
				cout << "You have defeated Azathoth!" << endl;
				ceremonyChamber->setEnemyDefeated(true);
				hasWon = true;
				cout << endl;
				pause();
			}
			if (health <= 0 && extralife == 1)
			{
				extralife--;
				cout << "You gasp for breath as one of Azathoth's tentacles knock you down." << endl;
				cout << "You quickly chug the elixer while you have the chance." << endl;
				cout << "A sense of renewed energy uplifts you." << endl;
				health = 50;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "You have been defeated by Azathoth.." << endl;
				isDead = true; 
				pause();
			}
		}
		else if (inInventory("Ornate Dagger") && !inInventory("Health Elixer"))
		{
			cout << "You hold your dagger steady as you prepare to take on your foe." << endl;
			while (azathoth->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "Azathoth is attacking!" << endl;
				enemyDmgDone = azathoth->rollToAtk();
				cout << "Azathoth does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 12 + 2;
				cout << "You attack Azathoth for " << playersDmg << " points of damage." << endl;
				azathoth->setHP(azathoth->getHP() - playersDmg);
				cout << "Azathoth now has " << azathoth->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (azathoth->getHP() <= 0)
			{
				cout << "You have defeated Azathoth!" << endl;
				ceremonyChamber->setEnemyDefeated(true);
				hasWon = true;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "Azathoth has defeated you..." << endl;
				isDead = true; //testing now.
				cout << endl;
				pause();
			}
		}
		else
		{
			cout << "Armed with nothing but your fist, you attempt to take down the monstrosity." << endl;
			while (azathoth->getHP() > 0 && health > 0)
			{
				int enemyDmgDone = 0;
				int enemyDmgTaken = 0;
				int newEnemyHP = 0;
				int playersDmg = 0;

				//enemy's turn
				cout << "Azathoth is attacking!" << endl;
				enemyDmgDone = azathoth->rollToAtk();
				cout << "Azathoth does " << enemyDmgDone << " points of damage." << endl;
				health -= enemyDmgDone;
				cout << "You now have " << health << " health points." << endl;
				cout << endl;

				//players turn
				playersDmg = rand() % 6 + 1;
				cout << "You attack Azathoth for " << playersDmg << " points of damage." << endl;
				azathoth->setHP(azathoth->getHP() - playersDmg);
				cout << "Azathoth now has " << azathoth->getHP() << " health points." << endl;
				cout << endl;
				pause();
			}
			if (azathoth->getHP() <= 0)
			{
				cout << "You have defeated Azathoth!" << endl;
				ceremonyChamber->setEnemyDefeated(true);
				hasWon = true;
				cout << endl;
				pause();
			}
			else if (health <= 0)
			{
				cout << "Azathoth has defeated you..." << endl;
				cout << endl;
				isDead = true; 
				pause();
			}
		}
			
	}

/*****************************************************************************************************
** Name: Foyer Search Function
** Description: Deals with the player using the rooms search menu. Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay. 
*****************************************************************************************************/
void Game::searchFoyer()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Investigate the painting on the wall." << endl;
				cout << "2. Check under the divan." << endl;
				cout << "3. Search the cabinets." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "The painting on the wall dipicts a bunch of women in the raw dancing around a large bonfire " << endl;
					cout << "under what appears to be an eclipsed moon. Something about the picture is quite unsettling. " << endl;
					cout << endl;
					pause();

					sanity--;

					//make option for if painting was already investigated.

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You check under the luxurious divan. " << endl;

					//if you haven't already recieved the item
					if (!inDiscardPile("Ornate Dagger") && !inInventory("Ornate Dagger"))
					{
						cout << "You found an Ornate Dagger."  << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//add Ornate Dagger to inventory
							inventory.push_back("Ornate Dagger");
							cout << "Ornate Dagger Obtained." << endl;
							cout << endl;
							pause();
						}
					}
					else
					{
						cout << "You've already checked here."  << endl;
						cout << endl;
						pause();
					}
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You search through the victorian cabinets" << endl;
					cout << "You find nothing of interest." << endl;
					cout << endl;
					pause();
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
		}

/*****************************************************************************************************
** Name: Study Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchStudy()
		{
			int choice;
			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Check the desk." << endl;
				cout << "2. Examine the Bust." << endl;
				cout << "3. Search the bookshelf." << endl;
				cout << "4. Back to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("Invalid choice. Enter a menu option instead:");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You check around the desk..." << endl;

					//if you haven't already recieved the item
					if (!inDiscardPile("Strange Note") && !inInventory("Strange Note"))
					{
						cout << "You find a strange note." << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							cout << endl;
							pause();
						}
						else
						{
							//read strange note.
							cout << "It reads:" << endl << endl;
							cout << "Alas, the time has finally arrived. The stars are aligned  and the ceremony " << endl;
							cout << "is ready to be performed. What splendors of knowledge..No, what vast power " << endl;
							cout << "will be my reward once the 'Ancient One' has awoken. To ensure there would " << endl;
							cout << "be no interferences I unfortunately had to have Mortimer silenced."  << endl;
							cout << endl;
							cout << "Glorious be the reign of AZATHOTH!," << endl << "G.W" << endl;
							cout << endl;

							//add Strange Note to inventory
							inventory.push_back("Strange Note");
							cout << "Strange Note obtained." << endl;
							cout << endl;
							pause();
						}
					}
					else
					{
						cout << "You've already looked here." << endl;
						cout << endl;
						pause();
					}

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You examine the crooked bust of one of the Westons and notice something shiny poking out from under. " << endl;

					//if you haven't already recieved the item
					if (!inDiscardPile("Old Brass Key") && !inInventory("Old Brass Key"))
					{
						cout << "You find an Old Brass Key." << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//add Old-Brass-Key to inventory
							inventory.push_back("Old Brass Key");
							cout << "Old Brass Key obtained." << endl;
							cout << endl;
							pause();
						}
					}
					else
					{
						cout << "You've already looked here!" << endl << endl;
						pause();
					}
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You search the large bookshelf for anything of interest." << endl;
					cout << "Most books seem to be about investments but a few of the newer ones seem "  << endl;
					cout << "to be about occult, ancient lore and alchemy." << endl;
					cout << "Otherwise you find nothing of interest."<< endl;
					cout << endl;
					pause();
				}
				else if (choice != 4)
					cout << "Invalid choice. Enter a menu option instead:" << endl;

			} while (choice != 4);
		}
/*****************************************************************************************************
** Name: Dining Room Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchDiningRoom()
		{
				int choice;

				do
				{
					resetConsole();

					cout << "What would you like to search?" << endl;
					cout << "1. Investigate the serving trolley." << endl;
					cout << "2. Check under the rug." << endl;
					cout << "3. Search the china cabinets." << endl;
					cout << "4. Return to room menu." << endl;
					cout << endl;

					//input validation
					choice = inputValidation("Enter your choice:");

					while (choice <= 0 || choice > 4)
						choice = inputValidation("The valid choices are 1-4. Please try again.");

					cout << endl;

					if (choice == 1)
					{
						resetConsole();
						cout << "You begin to uncover the serving dish and quickly back away in digust " << endl;
						cout << "as you smell the unidentified rotten meat." << endl;
						cout << endl;

					}
					else if (choice == 2)
					{
						resetConsole();
						cout << "You check under the thick turkish rug. " << endl;
						cout << "A strange insect like creature with tentacles shrieks " << endl;
						cout << "As it jumps on your face and bites you. You promptly " << endl;
						cout << "throw it off your face and squish it. What on earth was that " << endl;
						cout << "disturbing creature!?!. You begin to worry more about this place. " << endl;
						cout << endl;
						pause();
						sanity -= 10;
						health -= 10;
					}
					else if (choice == 3)
					{
						resetConsole();
						cout << "You search through the victorian china cabinets" << endl;
						cout << "You find nothing of interest....." << endl << endl;
						pause();
					}
					else if (choice != 4)
						cout << "The valid choices are 1 - 4. Please try again." << endl;

				} while (choice != 4);
			}
/*****************************************************************************************************
** Name: Kitchen Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchKitchen()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Investigate the corpse." << endl;
				cout << "2. Check the cabinets under the sink." << endl;
				cout << "3. Search the pantry." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You investigate the corpse.. " << endl;

					if (!inDiscardPile("Skeleton Key") && !inInventory("Skeleton Key"))
					{
						cout << "You find a Skeleton Key." << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//description
							cout << "This will certainly be useful for getting around the Manor. " << endl;
							cout << endl;

							//add skeleton key to inventory
							inventory.push_back("Skeleton Key");
							cout << "Skeleton Key Obtained." << endl;
							cout << endl;
							pause();
						}
					}
					else
					{
						cout << "You've already looked here." << endl << endl;
						pause();
					}

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You search under the sinks and dont find anything particulary unusual." << endl;
					cout << "Suddenly a sharp shreiking cry can be heard from right behind you." << endl;
					cout << "You bump your head on as you jump from being startled." << endl;
					cout << "Luckily the sound just came from a tea kettle on the stove top." << endl;
					cout << "You don't recall seeing it there before however, and with no-one around it seems quite out of place." << endl;
					cout << endl;
					health--;
					sanity--;
					pause();
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "The pantry is filled with a web of sticky odd anamolous fluid" << endl;
					cout << "You hear a disturbing buzz comming from deeper within the pantry and decide it best not to investigate further." << endl;
					cout << endl;
					pause();
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
			
		}

/*****************************************************************************************************
** Name: Hallway Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchHallway()
		{
			int choice;
			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Check the body of the hooded figure." << endl;
				cout << "2. Examine the Mirror." << endl;
				cout << "3. Back to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 3)
					choice = inputValidation("Invalid choice. Enter a menu option instead:");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You check the body.." << endl;

					//if you haven't already recieved the item
					if (!inDiscardPile("Strange Rune") && !inInventory("Strange Rune"))
					{
						cout << "You find a strange rune." << endl << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							cout << "The pentagonal-diamond shaped rune seems to pulsate with arcane energy. " << endl;
							cout << "You wonder what this could possibly be used for. " << endl;
							cout << endl;
							

							//add strange rune to inventory
							inventory.push_back("Strange Rune");
							cout << "Strange Rune obtained."  << endl;
							cout << endl;

							pause();
						}
					}
					else
					{
						cout << "You've already looked here." << endl << endl;
						pause();
					}

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You gaze into the mirror out of curiousity. " << endl;
					cout << "You catch the silloute of a figure passing behind you." << endl;
					cout << "You quickly turn around, but nothing is there." << endl;
					cout << endl;
					sanity--;
					pause();

				}
				else if (choice != 3)
					cout << "Invalid choice. Enter a menu option instead:" << endl;
			} while (choice != 3);
		}

/*****************************************************************************************************
** Name: Basement Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchBasement() //check
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Examine the relief." << endl;
				cout << "2. Check the old trunk." << endl;
				cout << "3. Search the furnace." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You examine the relief and notice a strange pentagonal socket..." << endl;
					cout << endl;
					if (inInventory("Strange Rune"))
					{
						cout << "You place the strange rune into the socket and hear a clicking sound." << endl;
						cout << "A portion of the wall slides away to reveal a secret passage." << endl;
						cout << endl;
						basement->setDoorToUnlock(true);
						inventory.remove("Strange Rune"); //testing
						discard.push_back("Strange Rune");

						//wait for the user to press enter before continuing 
						string pause;
						cout << "PRESS ENTER TO CONTINUE" << endl;
						getline(cin, pause);
						cin.clear();
						cin.ignore();
						cout << "\033[2J\033[1;1H";
					}
					else
					{
						cout << "Perhaps you can find something that will fit in here." << endl;
						cout << endl;

						//wait for the user to press enter before continuing 
						string pause;
						cout << "PRESS ENTER TO CONTINUE" << endl;
						getline(cin, pause);
						cin.clear();
						cin.ignore();
						cout << "\033[2J\033[1;1H";

					}
				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You check the old trunk to see if there is anything of interest." << endl;
					cout << "Inside you find all kinds of ancient relics, much like the kind you study." << endl;
					cout << "None of them would be useful at the moment." << endl;
					cout << endl;
					pause();
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You search the furnace...." << endl;
					cout << "The charred remains of several items can be found, but nothing that can be indentified." << endl;
					cout << endl;
					pause();
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
		}
/*****************************************************************************************************
** Name: Master B.R Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchMasterBedRoom()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Investigate the nightstand." << endl;
				cout << "2. Check the closet." << endl;
				cout << "3. Search under the bed." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You open up the nightstand... " << endl;
					cout << endl;
					//if you haven't already recieved the item
					if (!inDiscardPile("Dairy") && !inInventory("Dairy"))
					{
						cout << "You find a Dairy." << endl << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//read strange note.
							cout << "The only passages of interest read as follows:" << endl;
							cout << endl;
							cout << "A strange illness has befallen my beloved Edith. The doctors say they have never seen anything like it." << endl;
							cout << "They say there is no known cure. I refuse to accept that! I will find a way." << endl;
							cout << endl;
							cout << "My dear Edith was taken from me today. I curse the Gods for the unjustice they have done us!" << endl;
							cout << "Mortimer attempts to console me. He does not understand the pain I feel." << endl;
							cout << endl;
							cout << "I was visited by a odd fellow today. He claims he knows of a way to bring edith back." << endl;
							cout << "I dismissed this madman from my home, but he insisted I keep his number in case I changed my mind." << endl;
							cout << endl;
							cout << "Am I going insane?! Ever since that man visited, strange things have begun to occur." << endl;
							cout << "I have unexplainable nightmares, and I feel compelled to call him." << endl;
							cout << endl;
							cout <<" The entries end here." << endl;
							cout << endl;

							//add Strange Note to inventory
							inventory.push_back("Dairy");
							cout << "Dairy obtained."  << endl;
							cout << endl;

							pause();
						}
					}
					else
					{
						cout << "You've already looked here." << endl;
						cout << endl;
						pause();
					}
				}
				
				else if (choice == 2)
				{
					resetConsole();
					cout << "The closet is filled with fancy clothes and trinkets." << endl;
					cout << "You find nothing of interest...." << endl;
					cout << endl;
					pause();
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You find an old sturdy lockbox."  << endl;
					cout << endl;
					pause();
					if (inInventory("Old Brass Key"))
					{
						cout << "You use the Old Brass Key to open it up.." << endl;
						cout << endl;
						cout << "You find an unusual amulet with a note attached." << endl;
						cout << endl;
						cout << "The note reads: " << endl;
						cout << "Mortimer has gifted me this so called 'Elder Sign'." << endl;
						cout << "He claims it will protect me if my 'New Friends' seek to do me harm." << endl;
						cout << endl;
						//add elder sign
						
						if (!inDiscardPile("Elder Sign") && !inInventory("Elder Sign"))
						{
							cout << "You find the Elder Sign." << endl;
							cout << endl;

							//verify inventory has space
							if (inventory.size() == MAX_INVT_SIZE)
							{
								cout << "But you have no space in your inventory, discard and item first." << endl;
								pause();
							}
							else
							{

								//add elder sign to inventory
								inventory.push_back("Elder Sign");
								cout << "Elder Sign Obtained." <<endl;
								cout << endl;

								pause();
							}
						}
						else
						{
							cout << "You've already looked here." << endl << endl;
							pause();
						}
					}
					else
					{
						cout << "There seems to be no way of opening it without a key." << endl;
						cout << endl;
						pause();
					}
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
		}
/*****************************************************************************************************
** Name: Guest B.R Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchGuestRoom()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Check the closet." << endl;
				cout << "2. Investigate Vincent's body.." << endl;
				cout << "3. Check under the bed." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You open the closet door unleashing a bizarre miasma. " << endl;
					cout << "You temporarily hallucinate and begin to cough blood. " << endl;
					cout << "After a few minutes you feel normal enough to move on. " << endl; 
					cout << endl;
					sanity -= 5;
					health -= 5;
					pause();

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You search through Vicents pockets..." << endl;

					if (!inDiscardPile("Revolver") && !inInventory("Revolver"))
					{
						cout << "You found a Colt .38 revolver." << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//add Revolver to inventory
							inventory.push_back("Revolver");
							cout << "Revolver Obtained." << endl;
							cout << endl;

							pause();
						}
					}
					else
					{
						cout << "You've already checked here."  << endl;
						cout << endl;
						pause();
					}
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You check under the bed." << endl;
					cout << "You find nothing of interest....." << endl;
					pause();
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
		}
/*****************************************************************************************************
** Name: Ceremonial Chambers Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchCeremonyChamber()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Investigate the corpse." << endl;
				cout << "2. Check the cabinets under the sink." << endl;
				cout << "3. Search the pantry." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "There seems to be nothing of interest here. " << endl;
					cout << endl;

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "You find nothing of interest...." << endl;
					cout << endl;
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You find nothing of interest....."  << endl;
					cout << endl;
					//pause();
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);
		}
/*****************************************************************************************************
** Name: Conservatory Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchConservatory()
		{
				int choice;
				do
				{
					resetConsole();

					cout << "What would you like to search?" << endl;
					cout << "1. Invesitgate the dying plants." << endl;
					cout << "2. Examine the Fountain." << endl;
					cout << "3. Back to room menu." << endl;
					cout << endl;

					//input validation
					choice = inputValidation("Enter your choice:");

					while (choice <= 0 || choice > 3)
						choice = inputValidation("Invalid choice. Enter a menu option instead:");

					cout << endl;

					if (choice == 1)
					{
						resetConsole();
						cout << "The thorn riddled plants seem to twist and turn in unatural patterns." << endl;
						cout << "Something just isnt right about this place." << endl;
						cout << endl;
						pause();

					}
					else if (choice == 2)
					{
						resetConsole();
						cout << "You examine the now dried up fountain and notice a porcelain plaque." << endl;
						cout << endl;
						cout << "It reads:" << endl;
						cout << "'To my beloved Judith who filled me with light.'" << endl;
						cout << endl;
						cout << "Whoever she was, Judith seemed to be important to Giles Weston." << endl;
						cout << endl;
						pause();

					}
					else if (choice != 3)
						cout << "Invalid choice. Enter a menu option instead:" << endl;
				} while (choice != 3);
			}
		
/*****************************************************************************************************
** Name: Garden Search Function
** Description : Deals with the player using the rooms search menu.Some option allow the user to obtain
** items, while other options may harm the user or have no effect on gameplay.
*****************************************************************************************************/
		void Game::searchGarden()
		{
			int choice;

			do
			{
				resetConsole();

				cout << "What would you like to search?" << endl;
				cout << "1. Investigate the hole." << endl;
				cout << "2. Check out the workbench." << endl;
				cout << "3. Search the shed." << endl;
				cout << "4. Return to room menu." << endl;
				cout << endl;

				//input validation
				choice = inputValidation("Enter your choice:");

				while (choice <= 0 || choice > 4)
					choice = inputValidation("The valid choices are 1-4. Please try again.");

				cout << endl;

				if (choice == 1)
				{
					resetConsole();
					cout << "You investigate the hole and find nothing of interest... " << endl;
					cout << endl;
					pause();

				}
				else if (choice == 2)
				{
					resetConsole();
					cout << "The workbench seems to be some sort of alchemy table used for brewing poitions of sorts." << endl;
					if (!inDiscardPile("Health Elixer") && !inInventory("Health Elixer"))
					{
						cout << "You find a Health Elixer."  << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//description
							cout << "This vile of strange amber liquid labled 'Elixer of Health' may prove useful. " << endl;
							cout << endl;

							//add Health Elixer to inventory
							inventory.push_back("Health Elixer");
							extralife = 1;
							cout << "Health Elixer Obtained."  << endl;
							cout << endl;
							pause();
						}
					}
					else
					{
						cout << "You've already looked here."  << endl;
						cout << endl;
						pause();
					}
				}
				else if (choice == 3)
				{
					resetConsole();
					cout << "You open the shed to find the source of the light." << endl;
					cout << "A lantern iluminates the inside of the shed. You notice muddy footprints inside." << endl;
					cout << "You believe this latern will be of more use to you and decide to take it." << endl;
					cout << endl;
					
					if (!inDiscardPile("Lantern") && !inInventory("Lantern"))
					{
						cout << "You find a Lantern." << endl;
						cout << endl;

						//verify inventory has space
						if (inventory.size() == MAX_INVT_SIZE)
						{
							cout << "But you have no space in your inventory, discard and item first." << endl;
							pause();
						}
						else
						{
							//description
							cout << "This will be good for transversing dark rooms." << endl;
							cout << endl;

							//add lantern to inventory
							inventory.push_back("Lantern");
							cout << "Lantern Obtained." << endl;
							cout << endl;

							pause();
						}
					}
					else
					{
						cout << "You've already looked here."  << endl;
						cout << endl;
						pause();
					}
				}
				else if (choice != 4)
					cout << "The valid choices are 1 - 4. Please try again." << endl;

			} while (choice != 4);

		}
	
/*****************************************************************************************************
** Name: Inventory Search Function
** Description : Searches the players inventory to find a certain item and returns a boolian depending 
** on whether or not the item was found.
*****************************************************************************************************/
		bool Game::inInventory(string item)
		{
			//itarate through the inventory, if the item is found return true
			for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
			{
				if (*i == item)
					return true;
			}
			return false;
		}

		bool Game::inDiscardPile(std::string item)
		{
			//itarate through the discard pile, if the item is found return true
			for (list<string>::iterator i = discard.begin(); i != discard.end(); i++)
			{
				if (*i == item)
					return true;
			}
			return false;
		}

/*****************************************************************************************************
** Name: Inventory Management Function
** Description : Allows player to manage inventory by allowsing them to discard item not crucial to winning.
*****************************************************************************************************/
		void Game::manageInvt()
		{
			int count = 1;

			resetConsole();

			//display inventory
			cout << endl;
			cout << "Which item would you like to remove?" << endl;
			for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
			{
				cout << count << ". " << *i << endl;
				count++;
			}
			cout << count << ". Nevermind"  << endl;
			cout << endl;

			//ask the user which item they want to remove
			int choice = inputValidation("Enter your choice:");

			//validate input
			while (choice <= 0 || choice > count)
			{
				cout << "Invalid choice. Please enter one of the listed items instead." << endl;
				choice = inputValidation("Enter your choice:");
			}

			//if the user doesn't choose "nevermind", remove the selected item
			if (choice < count)
			{
				int countTwo = 0;
				int value = choice - 1;
				std::string item;

				//find the item that needs to be removed
				for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
				{
					if (countTwo == value)
						item = *i;

					countTwo++;
				}

				cout << endl;

			//check to make sure the item isn't necessary to win the game.
			if (item == "Lantern")
			{
				cout << "You will need this to see in dark places." << endl;
				cout << "Its best not to discard it right now." << endl;
				cout << endl;
				pause();
			}
			else if (item == "Revolver" || item == "Elder Sign")
			{
				cout << "You will probably use this to defend yourself." << endl;
				cout << "Its best not to discard it right now."  << endl;
				cout << endl;
				pause();
			}
			else if (item == "Skeleton Key")
			{
				cout << "You will need this to access certain rooms." << endl;
				cout << "Its best not to discard it right now."  << endl;
				cout << endl;
				pause();
			}
			else if (item == "Strange Rune")
			{
				cout << "You can't help but feel this is important." << endl;
				cout << "Its best not to discard it right now."  << endl;
				cout << endl;
				pause();
			}

			    //If uneccesary
					inventory.remove(item);
					discard.push_back(item);
					cout << "You have removed: " << item  << endl;
					cout << endl;
					pause();
			
			}
		}
/*****************************************************************************************************
** Name: Reset Console Function
** Description : Clears the console, then outputs the players status, inventory and
** room image. 
*****************************************************************************************************/
		void Game::resetConsole()
	{
		//code to clear the console
		cout << "\033[2J\033[1;1H"; //change for VS

		//display health sanity, and inventory
		cout << "HEALTH: " << health << endl;
		cout << "SANITY: " << sanity << endl;
		cout << "INVENTORY: ";
		for (list<string>::iterator i = inventory.begin(); i != inventory.end(); i++)
			cout << *i << "  ";
		cout << endl;
		cout << endl;

		//display room image
		curLoc->showImage();
	}

		void Game::pause()
		{
			//wait for the user to press enter before continuing 
			string pause;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			getline(cin, pause);
			cin.clear();
			cin.ignore();
			cout << "\033[2J\033[1;1H"; //comment out for VS
		}

/*****************************************************************************************************
** Name: Input validation Function
** Description : Makes sure the user enters a valid input when given choices.
*****************************************************************************************************/
	int Game::inputValidation(string prompt)
	{
		int num;

		//run the desired prompt
		cout << prompt << endl;
		cin >> num;

		//if the number entered was not an integer, prompt the user to try again
		while (!cin)
		{
			cout << "Invalid choice. Please enter an integer value instead." << endl;
			cin.clear();  //clear the error flag on cin
			cin.ignore(); //skip to the next new line
			cin >> num;
		}

		return num;
	}

/*****************************************************************************************************
** Name: Win Screen Function
** Description : Dislays win screen once player has won the game.
*****************************************************************************************************/
	void Game::winScreen()
	{
		// clear the console
			cout << "\033[2J\033[1;1H";

		//display the win screen image
		string imageLines = "";
		string fileName;

		ifstream inputFile;

		fileName = "EEWin.txt";

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

		//display win text
		cout << endl;
		cout << "The foul creature known as Azathoth is banished back to the realm from which it came." << endl;
		cout << "It is unfortunate that so many had to die, but at least you stoped that thing from being unleashed unto our world." << endl;
		cout << "You must now return to document your finding, but who else but you would believe such inconievable tale." << endl;
		cout << endl;
		cout << "THE END" << endl;
		cout << endl;
		pause();
	}

/*****************************************************************************************************
** Name: lose Screen Function
** Description : Dislays lose screen once player has died or gone insane.
*****************************************************************************************************/
	void Game::loseScreen()
	{
		//clear the console
		cout << "\033[2J\033[1;1H";

		//display the lose screen
		string imageLines = "";
		string fileName;

		ifstream inputFile;

		fileName = "EEGameOver.txt";

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

		//display final text
		cout << endl;
		cout << "GAME OVER!"  << endl;
		cout << endl;
		pause();
	}
	
