#pragma once

using namespace std;

#include <iostream>
#include <string>
#include <vector>

class Card {
public:
	// constants
	static const vector<char> SUITS;
	static const int MIN_FACE, MAX_FACE;

	// constructor
	Card();
	Card(int, char);
	Card(int, char, bool);
	Card(const Card&);

	// accessors
	const char getSuit();
	const int getFace();
	const int getValue();
	const bool isWildcard();
	const bool isJoker();
	const string toString();
	bool operator==(const Card&) const;
	bool operator<(const Card&) const;
	bool operator<=(const Card&) const;

	// mutators
	//void operator=(const Card& card);
	bool setSuit(char);
	bool setFace(int);
	Card updateWildcard(int);

private:
	// default values
	static const int DEFAULT_FACE;
	static const char DEFAULT_SUIT;

	// represents the card's suit (S/C/D/H/T/1/2/3)
	char m_suit;

	// represents the card's face (Deck.MIN_FACE - Deck.MAX_FACE)
	int m_face;

	// represents if the card is a wildcard in the current round
	bool m_wildcard;
};

