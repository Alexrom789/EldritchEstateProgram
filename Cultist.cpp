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

#include "Creature.hpp"
#include "Cultist.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector> 


using std::cin;
using std::cout;
using std::endl;
using std::vector;

Cultist::Cultist(int av, int an, int hp, string nm) : Creature (av, an, hp, nm)
{
}
