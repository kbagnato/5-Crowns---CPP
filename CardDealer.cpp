#include "CardDealer.h"
/* *********************************************************************
Function Name: CardDealer
Purpose: Constructor
Parameters: None
Return Value: none
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
CardDealer::CardDealer() {
	m_firstDeck = Deck();
	m_secondDeck = Deck();

	// seed random number generator
	std:srand(std::time(nullptr));
}

/* *********************************************************************
Function Name: toString
Purpose: Format both decks
Parameters: None
Return Value: A String with both decks
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
string CardDealer::toString() {
	return "Deck 1: " + m_firstDeck.toString() + "\n"
		+ "Deck 2: " + m_secondDeck.toString();
}

/* *********************************************************************
Function Name: dealCard
Purpose: Deal a random Card from either Deck
Parameters: None
Return Value: A random Card
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Card CardDealer::dealCard() {
	if (m_firstDeck.isEmpty()) {
		if (m_secondDeck.isEmpty()) {
			return Card();
		}
		else {
			return m_secondDeck.dealCard();
		}
	}
	else {
		if (m_secondDeck.isEmpty()) {
			return m_firstDeck.dealCard();
		}
		else {

			int choice = std::rand() % 2;
			if (0 == choice) {
				return m_firstDeck.dealCard();
			}
			else {
				return m_secondDeck.dealCard();
			}
		}

	}
}

/* *********************************************************************
Function Name: updateWildcards
Purpose: Update wildcard status in both decks
Parameters: int wildFace the current wildcard
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void CardDealer::updateWildcards(int wildFace) {
	m_firstDeck.updateWildcards(wildFace);
	m_secondDeck.updateWildcards(wildFace);
}
