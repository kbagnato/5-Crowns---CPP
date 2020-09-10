#pragma once

#include "Player.h"

class Human : public Player {
private:
	// constructor
	using Player::Player;

	// mutators (override Player functions)
	void drawCard(vector<Card>&, vector<Card>&);
	void discardCard(vector<Card>&);
	void assemble();
	void goOut();

	// help functions
	void offerHelpDraw(const vector<Card>, const vector<Card>);
	void offerHelpDiscard();
};