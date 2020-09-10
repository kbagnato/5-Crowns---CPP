#include "Deck.h"

/* *********************************************************************
Function Name: Deck
Purpose: Default Deck constructor
Parameters: None
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Deck::Deck() {
	m_cardVector = vector<Card>();

	// create a card of each face and suit and add it to the deck
	for (int suitIdx = 0; suitIdx < Card::SUITS.size(); suitIdx++) {
		for (int faceIdx = Card::MIN_FACE; faceIdx <= Card::MAX_FACE; faceIdx++) {
			m_cardVector.push_back(Card(faceIdx, Card::SUITS[suitIdx]));
		}
	}

	// add jokers
	for (int jokerSuit = 1; jokerSuit <= 3; jokerSuit++) {
		m_cardVector.push_back(Card(11, '0' + jokerSuit));
	}

	// shuffle the deck
	std::random_shuffle(m_cardVector.begin(), m_cardVector.end());
}

/* *********************************************************************
Function Name: toString
Purpose: Nicely format the Deck
Parameters: None
Return Value: A String representing the deck
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
string Deck::toString() {
	string result = "";
	
	// add all cards to string
	for (int count = 0; count < m_cardVector.size(); count++) {
		result += m_cardVector.at(count).toString() + " ";
	}

	return result;
}

/* *********************************************************************
Function Name: dealCard
Purpose: Remove the top Card from the Deck and return it
Parameters: None
Return Value: The Card removed from the Deck
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Card Deck::dealCard()
{
	// cannot deal from empty deck
	if (m_cardVector.empty()) {
		cout << "Failed to deal card from empty deck." << endl;
		return Card();
	}

	// get a copy of the first card
	Card topCard = m_cardVector.front();
	
	// remove first card
	m_cardVector.erase(m_cardVector.begin());

	return topCard;
}

/* *********************************************************************
Function Name: isEmpty
Purpose: Determine if the deck is empty
Parameters: None
Return Value: true if the deck is empty, else false
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
bool Deck::isEmpty() {
	return m_cardVector.size() == 0;
}

/* *********************************************************************
Function Name: updateWildcards
Purpose: Update the Cards wildcard status
Parameters:
	int face the current wildcard
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Deck::updateWildcards(int wildFace) {
	for (Card card : m_cardVector) {
		card.updateWildcard(wildFace);
	}
}