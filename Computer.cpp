#include "Computer.h"

/* *********************************************************************
Function Name: drawCard
Purpose: Move the first Card from the user-selected pile to the Player's hand
Parameters:
	vector<Card> drawPile the first pile to choose from
	vector<Card> discardPile the second pile to choose from
Return Value: None
Assistance Received: None
********************************************************************* */
void Computer::drawCard(vector<Card>& drawPile, vector<Card>& discardPile) {
	// get advice and reason from base class
	string reason;
	int choice = Player::helpDraw(drawPile, discardPile, reason);

	// print reasoning
	cout << "Computer is drawing the " << (choice == 0 ? drawPile.front().toString() : discardPile.front().toString())
		<< " from the " << (choice == 0 ? "draw" : "discard") << " pile because " << reason << endl;

	// choose from advised pile
	choice == 0 ? Player::drawCard(drawPile) : Player::drawCard(discardPile);
}

/* *********************************************************************
Function Name: assemble
Purpose: Allow the computer to rearrange the Cards in their hand
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Computer::assemble() {
	m_hand = helpAssemble();
}

/* *********************************************************************
Function Name: discardCard
Purpose: Move the user-selected Card from the Player's hand to the given pile
Parameters: None
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Computer::discardCard(vector<Card>& discardPile) {
	// get advice and reason from base class
	string reason;
	Card choice = Player::helpDiscard(reason);

	// print reasoning
	cout << "Computer is dropping the " << choice.toString() << " because " << reason << endl;

	// choose from advised pile
	Player::discardCard(choice, discardPile);
}

/* *********************************************************************
Function Name: goOut
Purpose: Go out if the computer can
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Computer::goOut() {
	if (canGoOut()) {
		Player::goOut();
	}
}