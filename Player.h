#pragma once

using namespace std;

#include <vector>
#include <string>

#include "Card.h"
#include "Assembler.h"

class Player {
public:
	// constructor
	Player();
	Player(const Player&);

	// getters
	string handToString();
	int getScore();
	int getPointsInHand();
	bool canGoOut();

	// mutators
	void setHand(vector<Card>);
	void setScore(int);
	void clearHand();
	void addCard(Card);
	bool addToScore(int);

	// utility functions
	void printHand();
	int play(vector<Card>&, vector<Card>&);
	int lastMove(vector<Card>&, vector<Card>&);


	Card helpDiscard(string&);
	
protected:
	// player's score
	int m_score;

	// player's hand
	vector<Card> m_hand;

	// turn functions
	virtual void assemble();
	virtual void goOut();
	virtual void drawCard(vector<Card>&);
	virtual void drawCard(vector<Card>&, vector<Card>&);
	virtual void discardCard(vector<Card>&);
	virtual void discardCard(int, vector<Card>&);
	virtual void discardCard(Card, vector<Card>&);

	// help functions (for Computer AI and user advice)
	int helpDraw(const vector<Card>, const vector<Card>, string&);
	vector<Card> helpAssemble();
	void removeDoubles(vector<Card>& hand);

	//// assembly logic functions
	//static vector<vector<Card>> removeAssemblies(vector<Card>&);
	//static vector<vector<Card>> removeAllBooks(vector<Card>&);
	//static vector<vector<Card>> removeAllRuns(vector<Card>&);
	//static vector<Card> removeFirstBook(vector<Card>&);
	//static vector<Card> removeFirstRun(vector<Card>&);
};