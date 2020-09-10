#include "Card.h"

// constants
const int Card::DEFAULT_FACE = 0;
const char Card::DEFAULT_SUIT = 'X';

const vector<char> Card::SUITS({ 'S', 'C', 'D', 'H', 'T' });
const int Card::MIN_FACE = 3, Card::MAX_FACE = 13;

/* *********************************************************************
Function Name: Card
Purpose: Default Card constructor
Parameters: None
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Card::Card() {
	m_face = DEFAULT_FACE;
	m_suit = DEFAULT_SUIT;
	m_wildcard = false;
}

Card::Card(const Card& inCard) {
	m_face = inCard.m_face;
	m_suit = inCard.m_suit;
	m_wildcard = inCard.m_wildcard;
}

/* *********************************************************************
Function Name: Card
Purpose: Card constructor
Parameters:
	char inSuit the suit to set
	int inFace the face to set
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Card::Card(int inFace, char inSuit) {
	// set face
	if (!setFace(inFace)) {
		cout << "Card class reports incorrect face: " << inFace << endl;
		cout << "Setting face to: " << DEFAULT_FACE << endl;
	}
	// set suit
	if (!setSuit(inSuit)) {
		cout << "Card class reports incorrect suit: " << inSuit << endl;
		cout << "Setting suit to: " << DEFAULT_SUIT << endl;
	}
	// not a wildcard by default
	m_wildcard = false;
}

Card::Card(int inFace, char inSuit, bool inWild) {
	Card(inFace, inSuit);
	m_wildcard = inWild;
}

/* *********************************************************************
Function Name: setSuit
Purpose: Set the Card's suit
Parameters:
	char inSuit the suit to set
Return Value: true if the suit is valid, false if not
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
bool Card::setSuit(char inSuit) {
	switch (inSuit) {
	case 'S':
	case 'H':
	case 'C':
	case 'D':
	case 'T':
	case '1':
	case '2':
	case '3':
		m_suit = inSuit;
		return true;
	default:
		m_suit = DEFAULT_SUIT;
		return false;
	}
}

/* *********************************************************************
Function Name: setFace
Purpose: Set the Card's face
Parameters:
	char inFace the face to set
Return Value: true if the face is valid, false if not
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
bool Card::setFace(int inFace) {
	if (inFace >= MIN_FACE && inFace <= MAX_FACE) {
		m_face = inFace;
		return true;
	}
	else {
		m_face = DEFAULT_FACE;
		return false;
	}
	return false;
}

/* *********************************************************************
Function Name: getSuit
Purpose: Get the Card's suit
Parameters: None
Return Value: the Card's suit
Assistance Received: None
********************************************************************* */
const char Card::getSuit() {
	return m_suit;
}

/* *********************************************************************
Function Name: getFace
Purpose: Get the Card's face
Parameters: None
Return Value: the Card's face
Assistance Received: None
********************************************************************* */
const int Card::getFace() {
	return m_face;
}

/* *********************************************************************
Function Name: getValue
Purpose: Get the Card's point value
Parameters: None
Return Value: the Card's face if 3-13
	20 if the Card is a wildcard
	500 if the Card is a joker
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
const int Card::getValue() {
	if (m_wildcard) {
		return 20;
	}

	if (isJoker()) {
		return 50;
	}

	return m_face;
}

/* *********************************************************************
Function Name: isWildcard
Purpose: Get the Card's wildcard status
Parameters: None
Return Value: the Card's wildcard status
Assistance Received: None
********************************************************************* */
const bool Card::isWildcard() {
	return m_wildcard;
}

/* *********************************************************************
Function Name: isJoker
Purpose: Get the Card's joker status
Parameters: None
Return Value: true if the Card is a joker, false if not
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
const bool Card::isJoker() {
	return (m_face == 11 && (m_suit == '1' || m_suit == '2' || m_suit == '3'));
}

/* *********************************************************************
Function Name: updateWildcard
Purpose: Set the Card's wildcard status
Parameters:
	int inFace the current round's wildcard face
Return Value: Itself
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Card Card::updateWildcard(int inFace) {
	if (m_face == inFace) {
		m_wildcard = true;
	}
	else {
		m_wildcard = false;
	}

	return *this;
}

/* *********************************************************************
Function Name: toString
Purpose: Return the Card as a String
Parameters: None
Return Value: The Card as a String
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
const string Card::toString() {
	switch (m_face) {
	case 10:
		return "X" + string(1, m_suit) + (isWildcard() ? "*" : "");
	case 11:
		return "J" + string(1, m_suit) + (isWildcard() ? "*" : "");
	case 12:
		return "Q" + string(1, m_suit) + (isWildcard() ? "*" : "");
	case 13:
		return "K" + string(1, m_suit) + (isWildcard() ? "*" : "");
	default:
		return to_string(m_face) + string(1, m_suit) + (isWildcard() ? "*" : "");
	}
}

// overload == operator
bool Card::operator== (const Card& rhs) const
{
	return rhs.m_face == m_face && rhs.m_suit == m_suit;
}

bool Card::operator< (const Card& rhs) const
{
	// sort by face
	if (m_face < rhs.m_face) {
		return true;
	}
	if (rhs.m_face < m_face) {
		return false;
	}

	// then sort by suit
	return m_suit < rhs.m_suit;
}

bool Card::operator<= (const Card& rhs) const
{
	// sort by face
	if (m_face < rhs.m_face) {
		return true;
	}
	if (rhs.m_face < m_face) {
		return false;
	}

	// then sort by suit
	return m_suit <= rhs.m_suit;
}