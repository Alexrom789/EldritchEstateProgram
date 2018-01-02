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

#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <string>

using std::string;

class Creature
{
protected:
	int attackDVal;
	int attackDNum;
	int healthPoints;
	string name;

public:
	Creature();
	Creature(int av, int an, int hp, string nm);

	virtual int rollToAtk();
	virtual int getHP();
	virtual string getName();
	virtual void setHP(int);
	virtual void setDVal(int);
};


#endif // !CREATURE_HPP
