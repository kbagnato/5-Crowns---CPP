#include "Human.h"

/* *********************************************************************
Function Name: drawCard
Purpose: Move the first Card from the user-selected pile to the Player's hand
Parameters:
	vector<Card> drawPile the first pile to choose from
	vector<Card> discardPile the second pile to choose from
Return Value: None
Assistance Received: None
********************************************************************* */
void Human::drawCard(vector<Card>& drawPile, vector<Card>& discardPile) {
	// offer help to the user
	offerHelpDraw(drawPile, discardPile);

	// ask which deck to draw from
	cout << "0. Draw Pile (??)" << endl;
	cout << "1. Discard Pile (" << discardPile.front().toString() << ")" << endl;

	string input;
	do {
		cout << "Enter a pile index to draw from: ";
		cin >> input;
	} while (!(input.compare("0") == 0 || input.compare("1") == 0));
	cout << endl;

	// verify pile is not empty
	if (input.compare("0") == 0 && drawPile.size() == 0) {
		cout << "You fool! The draw pile is empty." << endl;
		input = "1";
	}
	if (input.compare("1") == 0 && discardPile.size() == 0) {
		cout << "You fool! The discard pile is empty." << endl;
		input = "0";
	}

	// draw card from user-selected pile
	input.compare("0") == 0 ? Player::drawCard(drawPile) : Player::drawCard(discardPile);

	// print previousuly unknown Card
	if (input.compare("0") == 0) {
		cout << "You picked up a " << m_hand.back().toString() << "." << endl << endl;
	}
}

/* *********************************************************************
Function Name: offerHelpDraw
Purpose: Offer the user help choosing which pile to draw from
Parameters:
	vector<Card> drawPile the first pile to choose from
	vector<Card> discardPile the second pile to choose from
Return Value: None
Assistance Received: None
********************************************************************* */
void Human::offerHelpDraw(const vector<Card> drawPile, const vector<Card> discardPile) {
	string input;
	do {
		cout << "Do you want to help drawing a card? (Yes / No): ";
		cin >> input;
	} while (!(input.compare("Yes") == 0 || input.compare("No") == 0));
	cout << endl;

	// offer help if the user wants it
	if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
		// print advice and reason from base class
		string reason;
		int choice = Player::helpDraw(drawPile, discardPile, reason);

		// print reasoning
		cout << "You should draw from the " << (choice == 0 ? "draw" : "discard") << " pile because " << reason << endl;
	}
}

/* *********************************************************************
Function Name: discardCard
Purpose: Move the user-selected Card from the Player's hand to the given pile
Parameters: None
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Human::discardCard(vector<Card>& discardPile) {
	// offer help to the user
	offerHelpDiscard();

	// ask which card in hand to discard
	printHand();
	int input;
	do {
		cout << "Enter which card to discard: (0-" << (m_hand.size() - 1) << "): ";
		cin >> input;
	} while (input < 0 || input >= m_hand.size());
	cout << endl;

	// remove the given card
	Player::discardCard(input, discardPile);
}

/* *********************************************************************
Function Name: offerHelpDiscard
Purpose: Offer the user help choosing which Card to drop
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Human::offerHelpDiscard() {
	string input;
	do {
		cout << "Do you want to help dropping a card? (Yes / No): ";
		cin >> input;
	} while (!(input.compare("Yes") == 0 || input.compare("No") == 0));
	cout << endl;

	// offer help if the user wants it
	if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
		// print advice and reason from base class
		string reason;
		Card choice = Player::helpDiscard(reason);

		// print reasoning
		cout << "You should drop the " << choice.toString() << " because " << reason << endl;
	}
}


/* *********************************************************************
Function Name: assemble
Purpose: Allow the user to rearrange the Cards in their hand
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Human::assemble() {
	// ask user if they want to assemble
	string input;
	do {
		cout << "Do you want to assemble? (Yes / No): ";
		cin >> input;
	} while (!(input.compare("Yes") == 0 || input.compare("yes") == 0
		|| input.compare("No") == 0 || input.compare("no") == 0));
	cout << endl;

	// only continue if user wants to 
	if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
		
		// offer user auto sort
		do {
			cout << "Do you want to use auto-sort? (Yes / No): ";
			cin >> input;
		} while (!(input.compare("Yes") == 0 || input.compare("yes") == 0
			|| input.compare("No") == 0 || input.compare("no") == 0));
		cout << endl;

		// sort by face or suit
		if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
			m_hand = Player::helpAssemble();
			printHand();
		}
			

		// offer manually sort
		do {
			cout << "Do you want to manually re-order? (Yes / No): ";
			cin >> input;
		} while (!(input.compare("Yes") == 0 || input.compare("yes") == 0
			|| input.compare("No") == 0 || input.compare("no") == 0));
		cout << endl;

		// return if user does not want to assemble 
		if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
			// let user rearrange Cards in hand
			int card1, moveTo;
			string again;
			while (true) {
				printHand();

				// get first card index
				do {
					cout << "Enter the card index to move: ";
					cin >> card1;
				} while (card1 < 0 || card1 >= m_hand.size());

				// get second card index
				do {
					cout << "Enter the index to move to: ";
					cin >> moveTo;
				} while (moveTo < 0 || moveTo >= m_hand.size());

				// swap the Cards
				Card card = m_hand.at(card1);
				m_hand.erase(m_hand.begin() + card1);
				m_hand.insert(m_hand.begin() + moveTo, card);

				// print hand after swap
				printHand();

				// ask user if they want to continue swapping
				cout << "Continue? (Yes / No): ";
				cin >> again;
				if (again.compare("No") == 0 || again.compare("no") == 0) {
					break;
				}
			}
		}
	}
}


/* *********************************************************************
Function Name: goOut
Purpose: Ask the user if they want to go out and end the round
Parameters: None
Return Value: true if the player can successfully go out
Assistance Received: None
********************************************************************* */
void Human::goOut() {
	string input;
	do {
		cout << "Do you want to go out? (Yes / No): ";
		cin >> input;
	} while (!(input.compare("Yes") == 0 || input.compare("yes") == 0
		|| input.compare("No") == 0 || input.compare("no") == 0));
	cout << endl;

	// see if user can go out
	if (input.compare("Yes") == 0 || input.compare("yes") == 0) {
		if (canGoOut()) {
			Player::goOut();
		}
		else {
			cout << "You cannot go out at this time." << endl;
		}
	}
}