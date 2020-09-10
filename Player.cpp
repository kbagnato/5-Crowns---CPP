#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: Default constructor
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Player::Player() {
	m_score = 0;
	m_hand = vector<Card>(0);
}

/* *********************************************************************
Function Name: Player
Purpose: Copy constructor
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Player::Player(const Player& inPlayer) {
	m_score = inPlayer.m_score;
	m_hand = inPlayer.m_hand;
}

/* *********************************************************************
Function Name: handToString
Purpose: Nicely format the Player's hand
Parameters: None
Return Value: A String with the Player's hand
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
string Player::handToString() {
	string result = "";

	// add all cards to result
	for (Card card : m_hand) {
		result += card.toString() + " ";
	}

	return result;
}

/* *********************************************************************
Function Name: printHand
Purpose: Print the Player's hand to the console
Parameters: None
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Player::printHand() {
	cout << "Cards in hand:" << endl;;
	for (int i = 0; i < m_hand.size(); i++) {
		cout << i << ". " << m_hand.at(i).toString() << endl;
	}
	cout << endl;
}

/* *********************************************************************
Function Name: setHand
Purpose: Set the hand. Used for testing.
Parameters:
	vector<Card> inHand the hand to set
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::setHand(vector<Card> inHand) {
	m_hand = inHand;
}

/* *********************************************************************
Function Name: setScore
Purpose: Set the Player's score
Parameters:
	int inScore the score to set
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::setScore(int inScore)
{
	m_score = inScore;
}

/* *********************************************************************
Function Name: clearHand
Purpose: Empty the Player's hand
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::clearHand() {
	m_hand.clear();
}

/* *********************************************************************
Function Name: addCard
Purpose: Add a Card to the Player's hand
Parameters:
	Card newCard the Card to add
Return Value:
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Player::addCard(Card newCard) {
	// add new card to player's hand
	m_hand.push_back(newCard);
}

/* *********************************************************************
Function Name: play
Purpose: Step a player through their turn
Parameters:
	vector<Card> drawPile the draw pile
	vector<Card> discardPile the discard pile
Return Value:
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
int Player::play(vector<Card>& drawPile, vector<Card>& discardPile) {
	// draw card from DrawPile or DiscardPile
	drawCard(drawPile, discardPile);

	// let player rearrange their Cards
	assemble();

	// discard a card
	discardCard(discardPile);

	// check if all cards are assembled so player can go out
	goOut();

	// return points in hand
	return getPointsInHand();
}

/* *********************************************************************
Function Name: play
Purpose: Step a player through their turn
Parameters:
	vector<Card> drawPile the draw pile
	vector<Card> discardPile the discard pile
Return Value:
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
int Player::lastMove(vector<Card>& drawPile, vector<Card>& discardPile) {
	// pick up a Card from either given pile
	drawCard(drawPile, discardPile);

	// let player rearrange their Cards
	assemble();

	// drop a Card
	discardCard(discardPile);

	// remove all assemblies from the Player's hand
	Assembler bestAssembly = Assembler::getCheapestAssembly(Assembler(m_hand), Assembler());
	// print assemblies, remaining cards, score
	cout << bestAssembly.toString() << endl;

	// return points in hand
	return bestAssembly.getScore();
}

/* *********************************************************************
Function Name: drawCard
Purpose: Move the first Card from a given pile to the Player's hand
Parameters:
	vector<Card> drawPile the pile to choose from
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Player::drawCard(vector<Card>& drawPile) {
	// add the first Card in the draw pile
	addCard(drawPile.front());
	drawPile.erase(drawPile.begin());
}

/* *********************************************************************
Function Name: drawCard
Purpose: Move the first Card from a given pile to the Player's hand
Parameters:
	vector<Card> drawPile the first pile to choose from
	vector<Card> discardPile the second pile to choose from
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Player::drawCard(vector<Card>& drawPile, vector<Card>& discardPile) {
	// add the first Card in the draw pile
	addCard(drawPile.front());
	drawPile.erase(drawPile.begin());
}

/* *********************************************************************
Function Name: discardCard
Purpose: Move the first Card from the Player's hand to the given pile
Parameters:
	vector<Card> discardPile pile to move the Card to
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Player::discardCard(vector<Card>& discardPile) {
	// remove the first Card in hand
	discardPile.insert(discardPile.begin(), m_hand.front());
	m_hand.erase(m_hand.begin());
}

/* *********************************************************************
Function Name: discardCard
Purpose: Move the given Card index from the Player's hand to the given pile
Parameters:
	int cardToDrop the Card index to drop
	vector<Card> discardPile pile to move the Card to
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::discardCard(int cardToDrop, vector<Card>& discardPile) {
	// discard the user-selected card
	discardPile.insert(discardPile.begin(), m_hand.at(cardToDrop));
	// remove card from hand
	m_hand.erase(m_hand.begin() + cardToDrop);
}

/* *********************************************************************
Function Name: discardCard
Purpose: Move the given Card from the Player's hand to the given pile
Parameters:
	Card card the Card to drop
	vector<Card> discardPile pile to move the Card to
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::discardCard(Card card, vector<Card>& discardPile) {
	// discard the user-selected card
	discardPile.insert(discardPile.begin(), card);

	// find Card to remove
	for (int i = 0; i < m_hand.size(); i++) {
		// remove matching card from hand
		if (m_hand.at(i).getFace() == card.getFace() && m_hand.at(i).getSuit() == card.getSuit()) {
			m_hand.erase(m_hand.begin() + i);
			return;
		}
	}
}

/* *********************************************************************
Function Name: getScore
Purpose: Returns the Player's score
Parameters: None
Return Value: The Player's score
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
int Player::getScore() {
	return m_score;
}

/* *********************************************************************
Function Name: getPointsInHand
Purpose: Return the points in the Player's hand
Parameters: None
Return Value: The Player's points in hand
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
int Player::getPointsInHand() {
	int sum = 0;
	for (Card card : m_hand) {
		sum += card.getValue();
	}
	return sum;
}

/* *********************************************************************
Function Name: addToScore
Purpose: Add points to the Player's score
Parameters:
	int newPoints the points to add
Return Value: true if the points are positive, else false
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
bool Player::addToScore(int newPoints) {
	if (newPoints >= 0) {
		m_score += newPoints;
		return true;
	}
	else {
		cout << "Player class reports incorrect points: " << newPoints << endl;
		return false;
	}
}

/* *********************************************************************
Function Name: assemble
Purpose: Exist to be overwritten
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::assemble() {
	// do nothing
	cout << "Player::assemble() has yet to be overwritten." << endl;
}

/* *********************************************************************
Function Name: canGoOut
Purpose: Determine if all Cards can be assembled
Parameters: None
Return Value: true if the Player has no remaining Cards after assembly
Assistance Received: None
********************************************************************* */
bool Player::canGoOut() {
	// see if the player can assembly with no cards left over
	Assembler bestAssembly = Assembler::getCheapestAssembly(Assembler(m_hand), Assembler());
	return bestAssembly.getRemainingCards().size() == 0;
}

/* *********************************************************************
Function Name: goOut
Purpose: Remove and print all assemblies from hand
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::goOut() {
	cout << endl <<  "Going out!" << endl;

	// get best assembly from current hand
	Assembler bestAssembly = Assembler::getCheapestAssembly(Assembler(m_hand), Assembler());
	
	// print assemblies, remaining cards, score
	cout << bestAssembly.toString() << endl;

	// remove Cards from hand
	m_hand.clear();
	m_hand = vector<Card>(bestAssembly.getRemainingCards());
}

/* *********************************************************************
Function Name: helpDraw
Purpose: Advice the user what pile to draw from
Parameters:
	const vector<Card> drawPile the first pile to choose from
	const vector<Card> discardPile the second pile to choose from
	string &reason the reasong behind the advice
Return Value:
	0 if the draw pile should be chosen
	1 if the discard pile should be chosen
Assistance Received: None
********************************************************************* */
int Player::helpDraw(const vector<Card> drawPile, const vector<Card> discardPile, string& reason) {
	// check if either deck is empty
	if (drawPile.size() == 0) {
		reason = "the draw pile is empty.";
		return 0;
	}
	if (discardPile.size() == 0) {
		reason = "the discard pile is empty.";
		return 1;
	}

	// look at the top of the discard pile
	Card discardTopCard = discardPile.front();

	// check if discard pile is joker
	if (discardTopCard.isJoker()) {
		reason = "it is a Joker.";
		return 1;
	}
	// check if discard pile is wildcard
	if (discardTopCard.isWildcard()) {
		reason = "it is a wildcard.";
		return 1;
	}

	// check if the discard pile can be used in a book
	int faceToMatch = discardTopCard.getFace();
	int matchingFaces = 0;
	for (Card card : m_hand) {
		if (card.getFace() == faceToMatch) {
			matchingFaces++;
		}

		// use discard pile if book a valid book can be made
		if (matchingFaces >= 2) {
			// get face as character
			char face;
			switch (faceToMatch) {
			case 10:
				face = 'X';
				break;
			case 11:
				face = 'J';
				break;
			case 12:
				face = 'Q';
				break;
			case 13:
				face = 'K';
				break;
			default:
				face = '0' + faceToMatch;
				break;
			}
			reason = "to use it in a book of ";
			reason += face;
			reason += "s.";
			return 1;
		}
	}

	// check if the discard pile can be used in a run
	for (Card card : m_hand) {
		// use discard pile if it has a matching suit and is one face value away
		if (card.getSuit() == discardTopCard.getSuit()
			&& (card.getFace() - 1 == discardTopCard.getFace()
				|| card.getFace() + 1 == discardTopCard.getFace())) {

			reason = "to use it in a run with " + card.toString() + ".";
			return 1;
		}
	}

	// discard pile cannot help - draw from draw pile
	reason = "the " + discardTopCard.toString() + " cannot be used for an assembly.";
	return 0;
}

/* *********************************************************************
Function Name: helpAssemble
Purpose: Advice the Player how to order their Cards
Parameters: None
Return Value:
	vector<Card> the hand in suggested order: first all assemblies, then
	all remaining cards, followed by the one card removed
Assistance Received: None
********************************************************************* */
vector<Card> Player::helpAssemble() {
	// iterate through the hand N times with one card removed eached time
	for (int i = 0; i < m_hand.size(); i++) {
		// remove card from copy of hand
		vector<Card> handWithoutCard = vector<Card>(m_hand);
		handWithoutCard.erase(handWithoutCard.begin() + i);

		// get best assembly
		Assembler assembly = Assembler::getCheapestAssembly(Assembler(handWithoutCard), Assembler());

		// check if all cards are assembled
		if (assembly.getRemainingCards().size() == 0) {
			// return cards in order with removed card at the end
			vector<Card> result = assembly.getAssemblies().front();
			result.push_back(m_hand.at(i));
			return result;
		}
	}

	return Assembler::getCheapestHand(m_hand);
}

/* *********************************************************************
Function Name: removeDoubles
Purpose: Remove books/runs of length 2
Parameters:
	vector<Card>& hand the hands to remove doubles from
Return Value: None
Assistance Received: None
********************************************************************* */
void Player::removeDoubles(vector<Card>& hand) {
	if (hand.size() == 0) {
		return;
	}
	
	for (int i = 0; i < hand.size() - 1; i++) {
		// remove almost-books
		if (hand.at(i).getFace() == hand.at(i + 1).getFace() || hand.at(i + 1).isWildcard() || hand.at(i + 1).isJoker()) {
			hand.erase(hand.begin() + i);
			hand.erase(hand.begin() + i);
		}

		// remove almost-runs
		else if (
			hand.at(i).isJoker() || hand.at(i).isWildcard() || 
			hand.at(i + 1).isJoker() || hand.at(i + 1).isWildcard()
			|| (
				hand.at(i).getSuit() == hand.at(i + 1).getSuit()
				&& (hand.at(i).getFace() == hand.at(i + 1).getFace() + 1)
				|| hand.at(i).getFace() == hand.at(i + 1).getFace() - 1)) {
			hand.erase(hand.begin() + i);
			hand.erase(hand.begin() + i);
		}
		else {
			i++;
		}

		if (hand.size() < 2) {
			break;
		}
	}
}

/* *********************************************************************
Function Name: helpDiscard
Purpose: Advice the user what Card to drop
Parameters:
	string &reason the reasong behind the advice
Return Value:
	Card the Card to drop
Assistance Received: None
********************************************************************* */
Card Player::helpDiscard(string& reason) {
	// build assemblies on copy deck
	// check what is not used (copy is modified)
	// if only one, drop it

	// see if one card can be dropped and the others assembled
	for (int cardDropped = 0; cardDropped < m_hand.size(); cardDropped++) {
		vector<Card> handWithoutOne = vector<Card>(m_hand);
		handWithoutOne.erase(handWithoutOne.begin() + cardDropped);

		// check if all cards are assembled
		if (Assembler::getCheapestAssembly(Assembler(handWithoutOne), Assembler()).getRemainingCards().size() == 0) {
			reason = "all other cards can be assembled.";
			return m_hand.at(cardDropped);
		}
	}
	
	// get best assembly (books and runs, remaining cards)
	Assembler bestAssembly = Assembler::getCheapestAssembly(Assembler(m_hand), Assembler());
	vector<Card> handCopy = bestAssembly.getRemainingCards();
	vector<vector<Card>> assemblies = bestAssembly.getAssemblies();

	// remove double cards from hand
	removeDoubles(handCopy);

	// remove first Card not used in assembly
	if (handCopy.size() > 0) {
		// don't drop a card if it has the potential to be used for a book or run
		for (int i = 0; i < handCopy.size() - 1; i++) {
			int face = handCopy.at(i).getFace();
			char suit = handCopy.at(i).getSuit();

			bool useful = false;
			// loop through the following cards in the hand
			for (int j = i + 1; j < handCopy.size(); j++) {

				// see if Card can be used for book
				if (handCopy.at(j).getFace() == face) {
					useful = true;
				}

				// see if Card can be used for run
				if (handCopy.at(j).getSuit() == suit
					&& (handCopy.at(j).getFace() - m_hand.size() + 2 <= face
						|| handCopy.at(j).getFace() + m_hand.size() - 2 >= face)) {
					useful = true;
				}

			}
			// determine if card is useful after checking following cards 
			if (!useful) {
				reason = "it is not close to an assembly.";
				return handCopy.at(i);
			}
		}

		// drop the Card with the highest value
		int highestIdx = 0;
		int highestValue = handCopy.at(highestIdx).getValue();
		for (int i = 0; i < handCopy.size(); i++) {
			// store highest index (besides jokers/wildcards)
			if (!(handCopy.at(i).isJoker() || handCopy.at(i).isWildcard()) && handCopy.at(i).getValue() > highestValue) {
				highestIdx = i;
				highestValue = handCopy.at(highestIdx).getValue();
			}
		}
		reason = "it has the highest value between the unused cards.";
		return handCopy.at(highestIdx);
	}
	else {
		// all cards are in assemblies - drop a card from the biggest one

		// find the largest assembly
		int largestSize = 0;
		int assemblyIdx = -1;
		for (int i = 0; i < assemblies.size(); i++) {
			if (assemblies.at(i).size() > largestSize) {
				assemblyIdx = i;
			}
		}

		// get the first Card in the largest assembly
		Card card = assemblies.at(assemblyIdx).front();
		reason = "it is from the largest assembly.";
		return card;
	}
}