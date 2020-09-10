#pragma once
using namespace std;

#include <vector>
#include <algorithm>

#include "Card.h"

class Deck {
public:
	// constants
	static const int DECK_SIZE;

	// constructors
	Deck();
//	Deck(const Deck&);

	// accessors
	string toString();
	bool isEmpty();

	// mutators
	Card dealCard();
	void updateWildcards(int);


protected:
private:
	// cards in the deck
	vector<Card> m_cardVector;
};