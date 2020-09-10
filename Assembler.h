#pragma once

#include "Card.h"
#include "Player.h"

#include <vector>
#include <algorithm>"

class Assembler {

public:
	
	// constructors
	Assembler();
	Assembler(vector<Card>);
	Assembler(vector<vector<Card>>, vector<Card>);
	Assembler(const Assembler&);

	// accessors
	vector<vector<Card>> getAssemblies();
	vector<Card> getRemainingCards();
	int getScore();
	bool isEmpty();
	string toString();
	
	// utility
	static vector<Card> getCheapestHand(const vector<Card>);
	static Assembler getCheapestAssembly(const Assembler, const Assembler);

	static bool isRun(const vector<Card>);
	static bool isBook(const vector<Card>);
private:
	// member variables
	vector<vector<Card>> m_assemblies;
	vector<Card> m_remainingCards;

	// mutators
	void setAssemblies(vector<vector<Card>>);
	void setRemainingCards(vector<Card>);
	void removeAssembly(vector<Card>);

	// utility
	static vector<Card> sortHandByFace(const vector<Card>);
	static vector<Card> sortHandBySuit(const vector<Card>);
	static vector<vector<Card>> getAllAssemblies(vector<Card>);
	static vector<vector<Card>> getAllBooks(const vector<Card> inHand);
	static vector<vector<Card>> getAllRuns(const vector<Card> inHand);
	//vector<Card> next_permutation(const vector<Card> inHand);
	//vector<Card> reverse(const vector<Card> inHand, int start);
};

