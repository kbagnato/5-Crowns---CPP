#pragma once

#include "Player.h"

class Computer : public Player {
private:
	// constructor
	using Player::Player;

	// mutators (override Player functions)
	void drawCard(vector<Card>&, vector<Card>&);
	void discardCard(vector<Card>&);
	void assemble();
	void goOut();
};