#pragma once

#include "Human.h"
#include "Computer.h"
#include "Round.h"

class Game {
public:
	// constructor
	Game();


	// start the game
	void play();

private:
	// players
	Human m_human;
	Computer m_computer;

	// current round number
	int m_roundNum;

	// next player index
	int m_nextPlayerIdx;

	// constants
	const int NUM_PLAYERS = 2;
	const int MAX_ROUND = 11;
};