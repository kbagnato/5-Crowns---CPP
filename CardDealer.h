#pragma once

#include <string>
#include <ctime>

#include "Deck.h"

class CardDealer {
public:
	// constructor
	CardDealer();

	// accessor
	string toString();

	// utililty function
	Card dealCard();

	// mutator function
	void updateWildcards(int);


private:
	// the decks to deal from
	Deck m_firstDeck, m_secondDeck;
};