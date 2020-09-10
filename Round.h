#pragma once

#include <iostream>	
#include <fstream>
#include <string>

#include "CardDealer.h"
#include "Human.h"
#include "Computer.h"

class Round {
public:
	// constants
	static const int TOTAL_PLAYERS;

	// constructors
	Round();
	Round(int, int, Human*, Computer*);

	// accessors
	void printRound();
	int getNextPlayerIdx();
	int getRoundNum();

	// mutator
	void setNextPlayerIdx(const int);

	// utility functions
	void play();
	void serialize();

private:
	// current round
	int m_roundNum;

	// player array and index
	vector<Player*> m_playerVector;
	int m_nextPlayerIdx;

	// CardDealer for the round
	CardDealer m_cardDealer;

	// draw and discard piles for the round
	vector<Card> m_drawPile;
	vector<Card> m_discardPile;
	
	// utility functions
	void coinToss();
	void save(string);
	void load(string);
	vector<Card> stringToVector(const string);
};