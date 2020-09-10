#include "Assembler.h"

/* *********************************************************************
Function Name: Player
Purpose: Default constructor
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Assembler::Assembler() {
	m_assemblies = vector<vector<Card>>();
	m_remainingCards = vector<Card>();
}

/* *********************************************************************
Function Name: Assembler
Purpose: Constructor
Parameters:
	vector<Card> inRemainingCards the remaining cards to begin with
Return Value: None
Assistance Received: None
********************************************************************* */
Assembler::Assembler(vector<Card> inRemainingCards) {
	m_assemblies = vector<vector<Card>>();
	m_remainingCards = vector<Card>(inRemainingCards);
}

/* *********************************************************************
Function Name: Assembler
Purpose: Initialize with assemblies and remaining cards
Parameters:
	vector<vector<Card>> inAssemblies the assemblies to initalize with
	vector<Card> inRemainingCards the remaining cards to initalize with
Return Value: None
Assistance Received: None
********************************************************************* */
Assembler::Assembler(vector<vector<Card>> inAssemblies, vector<Card> inRemainingCards) {
	m_assemblies = vector<vector<Card>>(inAssemblies);
	m_remainingCards = vector<Card>(inRemainingCards);
}

/* *********************************************************************
Function Name: Assembler
Purpose: Copy constructor
Parameters:
	const Assembler& inAssembler the assembler to initalize with
Return Value: None
Assistance Received: None
********************************************************************* */
Assembler::Assembler(const Assembler& inAssembler) {
	m_assemblies = vector<vector<Card>>(inAssembler.m_assemblies);
	m_remainingCards = vector<Card>(inAssembler.m_remainingCards);
}

/* *********************************************************************
Function Name: compareCards
Purpose: Utililty structure for next_permutation
Parameters: None
Return Value: None
Assistance Received:
	https://stackoverflow.com/questions/24150840/next-permutation-compare-function
********************************************************************* */
struct compareCards {
	bool operator()(Card& c1, Card& c2) const {
		// sort by face
		if (c1.getFace() > c2.getFace()) {
			return true;
		}
		else {
			// sort by suit
			if (c1.getSuit() < c1.getSuit()) {
				return true;
			}
		}
		return false;
	}
};

/* *********************************************************************
Function Name: getAllAssemblies
Purpose: Get all possible books and run that can be made from the given hand
Parameters:
	vector<Card> inHand the hand to look for assemblies in
Return Value:
	vector<vector<Card>> the list of all possible assemblies
Assistance Received: None
********************************************************************* */
vector<vector<Card>> Assembler::getAllAssemblies(const vector<Card> inHand) {
	// total list of books
	vector<vector<Card>> allAssemblies;

	// get books and runs
	vector<vector<Card>> books = getAllBooks(inHand);
	vector<vector<Card>> runs = getAllRuns(inHand);

	// check if the entire are a book or a run
	if (isBook(inHand) || isRun(inHand)) {
		// move cards from remaining to assembled
		allAssemblies.push_back(vector<Card>(inHand));
	}

	// concatenate lists
	allAssemblies.reserve(books.size() + runs.size());
	allAssemblies.insert(allAssemblies.end(), books.begin(), books.end());
	allAssemblies.insert(allAssemblies.end(), runs.begin(), runs.end());

	// return list
	return allAssemblies;
}

/* *********************************************************************
Function Name: getAllBooks
Purpose: Return all books from the given hand
Parameters:
	vector<Card> inHand the hand to check for books
Return Value:
	vector<vector<Card>> the list of all possible books
Assistance Received: None
********************************************************************* */
vector<vector<Card>> Assembler::getAllBooks(const vector<Card> inHand) {
	// create a list of all possible assemblies from given hand
	vector<vector<Card>> allBooks = vector<vector<Card>>();

	// try to make an assembly starting with each card
	for (int startIdx = 0; startIdx < inHand.size(); startIdx++) {
		vector<Card> hand = vector<Card>(inHand);
		vector<Card> possibleBook = vector<Card>();

		// start possible assemblies with start card
		possibleBook.push_back(hand.at(startIdx));

		// remove card from hand to avoid double counting
		hand.erase(hand.begin() + startIdx);

		// store face and suit for convenience
		int face = possibleBook.at(0).getFace();

		// see if other cards can be used for books 
		vector<Card> handFaceSort = sortHandByFace(hand);
		for (int cmpIdx = 0; cmpIdx < handFaceSort.size(); cmpIdx++) {
			// check for possible book
			if (handFaceSort.at(cmpIdx).isJoker()
				|| handFaceSort.at(cmpIdx).isWildcard()
				|| face == handFaceSort.at(cmpIdx).getFace()) {
				possibleBook.push_back(handFaceSort.at(cmpIdx));

				// add valid book to return value
				if (isBook(possibleBook)) {
					allBooks.push_back(possibleBook);

					// create copy of self to avoid overwriting existing assemblies
					possibleBook = vector<Card>(possibleBook);
				}
			}
		}
	}

	// remove assemblies from the list (if there are any)
	if (allBooks.size() != 0) {
		// compare each card (left hand side) to each following card
		for (int lhs = 0; lhs < allBooks.size() - 1; lhs++) {
			// check if right hand side matches lhs
			for (int rhs = lhs + 1; rhs < allBooks.size(); rhs++) {
				if (sortHandBySuit(allBooks.at(lhs)) == sortHandBySuit(allBooks.at(rhs))) {
					allBooks.erase(allBooks.begin() + rhs);
					rhs--;
				}
			}
		}
	}

	// return list of all possible assemblies
	return allBooks;
}

/* *********************************************************************
Function Name: getAllRuns
Purpose: Return all runs from the given hand
Parameters:
	vector<Card> inHand the hand to check for runs
Return Value:
	vector<vector<Card>> the list of all possible runs
Assistance Received: None
********************************************************************* */
vector<vector<Card>> Assembler::getAllRuns(const vector<Card> inHand) {
	// create a list of all possible assemblies from given hand
	vector<vector<Card>> allRuns = vector<vector<Card>>();

	/*
	go through all permutations of hand
	for each one
	if (length 3+ && isRun) add to list
	remove duplicates
	return list
	*/
	// look at all permutations of hand (to deal with any wildcards/jokers at any location)
	
	// create copy of given hand and sort through all perumtations
	vector<Card> hand = vector<Card>(inHand);
	sort(hand.begin(), hand.end(), compareCards());
	do {
		// try to make run with cards from i to i+3->hand.size()
		for (int i = 2; i < hand.size(); i++) {
			if (isRun(vector<Card>(hand.begin(), hand.begin() + i))) {
				allRuns.push_back(vector<Card>(hand.begin(), hand.begin() + i));
			}
		}
		// load next perumtation
	} while (std::next_permutation(begin(hand), end(hand), compareCards()));

	// remove assemblies from the hand
	if (allRuns.size() != 0) {
		// compare each card (left hand side) to each following card
		for (int lhs = 0; lhs < allRuns.size() - 1; lhs++) {
			// check if right hand side matches lhs
			for (int rhs = lhs + 1; rhs < allRuns.size(); rhs++) {
				if (sortHandBySuit(allRuns.at(lhs)) == sortHandBySuit(allRuns.at(rhs))) {
					allRuns.erase(allRuns.begin() + rhs);
					rhs--;
				}
			}
		}
	}

	// return list of all possible assemblies
	return allRuns;
}

/* *********************************************************************
Function Name: getCheapestAssembly
Purpose: Determine the cheapest assembly from the given assembly
Parameters:
	Assembler inAssembly the node to determine the cheapest assembly from
	Assembler cheapestChild the cheapest child (collecting the children
		along its recursive calls)
Return Value:
	Assembler the best assembly possible
Assistance Received: Dr. Kumar
********************************************************************* */
Assembler Assembler::getCheapestAssembly(Assembler inAssembly, Assembler cheapestChild) {
	// print current assembly
	//cout << "Node: " << inAssembly.toString() << endl;

	// make a list of all possible assemblies from remaining cards
	vector<vector<Card>> allAssemblies = getAllAssemblies(inAssembly.getRemainingCards());

	// check if assemblies can be made from hand
	if (allAssemblies.size() == 0 || inAssembly.m_remainingCards.size() == 0) {
		// no possible assemblies remaining
		//cout << "No further assemblies, returning self" << endl << endl;
		return inAssembly;
	}
	else {
		// create children nodes
		vector<Assembler> children;

		// populate each child with one assembly removed
		for (vector<Card> assembly : allAssemblies) {
 			Assembler child = Assembler(inAssembly);
			child.removeAssembly(assembly);
			children.push_back(child);
		}

		//// print children
		//cout << "Children: " << endl;
		//for (Assembler child : children) {
		//	cout << "\t" << child.toString() << endl;
		//}
		//cout << endl;

		// find the cheapest node of the chldren
		for (Assembler child : children) {
			if (cheapestChild.isEmpty() ||
				child.getCheapestAssembly(child, cheapestChild).getScore() < cheapestChild.getScore()) {
				cheapestChild = child.getCheapestAssembly(child, cheapestChild);
			}
		}

		// print cheapest child
		//cout << "Cheapest child: " << cheapestChild.toString() << endl << endl;
		return cheapestChild;
	}
}

/* *********************************************************************
Function Name: getCheapestHand
Purpose: Determine the best order of the cards, starting with assemblies
	followed by the remaining cards
Parameters:
	vector<Card> inHand the hand to get the best order from
Return Value:
	vector<Card> the hand in order: assemblies, remaining cards
Assistance Received: None
********************************************************************* */
vector<Card> Assembler::getCheapestHand(const vector<Card> inHand) {
	// get the best assenbly from the given hand
	Assembler bestAssembly = Assembler::getCheapestAssembly(Assembler(inHand), Assembler());

	// value to return 
	vector<Card> result = vector<Card>();

	// add all assemblies to hand
	for (vector<Card> assembly : bestAssembly.getAssemblies()) {
		// add all cards in assembly
		for (Card card : assembly) {
			result.push_back(card);
		}
	}

	// add all remaining cards to hand
	for (Card card : bestAssembly.getRemainingCards()) {
		result.push_back(card);
	}

	// return all cards in bestAssembly
	return result;
}

/* *********************************************************************
Function Name: isEmpty
Purpose: Determine if there are cards in the assembly
Parameters: None
Return Value:
	true if there are no assemblies and no remaining cards
Assistance Received: None
********************************************************************* */
bool Assembler::isEmpty() {
	return (m_assemblies.size() == 0 && m_remainingCards.size() == 0);
}

/* *********************************************************************
Function Name: getAssemblies
Purpose: Return all member assemblies
Parameters: None
Return Value:
	vector<vector<Card>> the list of all established assemblies
Assistance Received: None
********************************************************************* */
vector<vector<Card>> Assembler::getAssemblies() {
	return m_assemblies;
}

/* *********************************************************************
Function Name: getRemainingCards
Purpose: Return all remaining cards
Parameters: None
Return Value:
	vector<Card> all established remaining cards
Assistance Received: None
********************************************************************* */
vector<Card> Assembler::getRemainingCards() {
	return m_remainingCards;
}

/* *********************************************************************
Function Name: getScore
Purpose: Return the sum score of all remaining cards
Parameters: None
Return Value:
	int the sum score of all remaining cards
Assistance Received: None
********************************************************************* */
int Assembler::getScore() {
	// reset score
	int score = 0;

	// add points to score
	for (Card card : m_remainingCards) {
		score += card.getValue();
	}

	return score;
}

/* *********************************************************************
Function Name: toString
Purpose: Return the assembly as a string
Parameters: None
Return Value:
	string the list of assemblies, remaining cards, and score
Assistance Received: None
********************************************************************* */
string Assembler::toString() {
	string result = "(";

	// add assemblies
	result += "Assemblies: [";
	for (vector<Card> assembly : m_assemblies) {
		result += "[";
		for (Card card : assembly) {
			result += card.toString() + " ";
		}
		result += "]";
	}
	result += "], ";

	// add remaining cards
	result += "Remaining cards: [";
	for (Card card : m_remainingCards) {
		result += card.toString() + " ";
	}
	result += "], ";

	// add score
	result += "Score: " + std::to_string(getScore()) + ")";

	return result;
}

/* *********************************************************************
Function Name: setAssemblies
Purpose: Set all member assemblies
Parameters:
	vector<vector<Card>> the list of assemblies to set
Return Value: None
Assistance Received: None
********************************************************************* */
void Assembler::setAssemblies(vector<vector<Card>> inAssemblies) {
	m_assemblies.clear();
	m_assemblies = inAssemblies;
}

/* *********************************************************************
Function Name: setRemainingCards
Purpose: Set all remaining cards
Parameters:
	vector<Card> the remaining cards to set
Return Value: None
Assistance Received: None
********************************************************************* */
void Assembler::setRemainingCards(vector<Card> inRemainingCards) {
	m_remainingCards = inRemainingCards;
}

/* *********************************************************************
Function Name: removeAssembly
Purpose: Move a hand from remaining cards to list of assembly
Parameters:
	vector<Card> assembly the list of cards to move
Return Value: None
Assistance Received: None
********************************************************************* */
void Assembler::removeAssembly(vector<Card> assembly) {
	// add assembly to list
	m_assemblies.push_back(assembly);

	// remove assembly from remaining cards
	// look through all cards to remove
	for (Card cardToRemove : assembly) {
		// look through all cards in remaining hand
		for (int i = 0; i < m_remainingCards.size(); i++) {
			// check if current card in hand matches current card to remove
			if (m_remainingCards.at(i).getFace() == cardToRemove.getFace() && m_remainingCards.at(i).getSuit() == cardToRemove.getSuit()) {
				// remove card from hand
				m_remainingCards.erase(m_remainingCards.begin() + i);
				// decrement search index to check the following card (now in the same place)
				i--;
				// only remove one card
				break;
			}
		}
	}
}

/* *********************************************************************
Function Name: isRun
Purpose: Determine if the given cards are a valid run
Parameters:
	vector<Card> hand the list of cards to check
Return Value:
	true if the given cards are a valid run
Assistance Received:
	https://stackoverflow.com/questions/24150840/next-permutation-compare-function
********************************************************************* */
bool Assembler::isRun(vector<Card> hand) {
	// run must be 3 or more cards long
	if (hand.size() < 3) {
		return false;
	}

	// sort by suit, face
	// count/remove all jokers/wildcards
	// if run is about to break, try to use joker/wildcard if it's not possible

	hand = sortHandBySuit(hand);
	int totalWilds = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i).isJoker() || hand.at(i).isWildcard()) {
			totalWilds++;
			hand.erase(hand.begin() + i);
			i--;
		}
	}

	// cards must have matching suit
	int suitToMatch = hand.at(0).getSuit();

	// track current face to determine if next card follows
	int currentFace = hand.at(0).getFace();

	// check cards by stepping through pairs in the hand
	for (int leftCard = 0; leftCard < hand.size() - 1; leftCard++) {
		int rightCard = leftCard + 1;

		//			// no need to compare jokers/wildcards
		//			if (hand.get(leftCard).isJoker() || hand.get(leftCard).isWildcard()
		//					|| hand.get(rightCard).isJoker() || hand.get(rightCard).isWildcard()) {
		//				currentFace++;
		//				continue;
		//			}

					// cards must match suit
		if (hand.at(rightCard).getSuit() != suitToMatch) {
			if (totalWilds > 0) {
				totalWilds--;
				leftCard--;
			}
			else {
				return false;
			}
		}

		// check if rightCard is one face higher than leftCard
		if (hand.at(rightCard).getFace() != currentFace + 1) {
			if (totalWilds > 0) {
				totalWilds--;
				leftCard--;
			}
			else {
				return false;
			}
		}

		// go to next face
		currentFace++;
	}

	// no cards failed test
	return true;

/** being replaced with above */
	//// run must be 3 or more cards long
	//if (hand.size() < 3) {
	//	return false;
	//}

	//// extract all wilds
	//int totalWilds = 0;
	//for (int i = 0; i < hand.size(); i++) {
	//	if (hand.at(i).isJoker() || hand.at(i).isWildcard()) {
	//		totalWilds++;
	//		hand.erase(hand.begin() + i);
	//		i--;
	//	}
	//}

	//// sort by suit, face to align runs
	//hand = Assembler::sortHandBySuit(hand);



	////// look at all permutations of hand (to deal with any wildcards/jokers at any location)
	////sort(hand.begin(), hand.end(), compareCards());
	////do {
	//	// try to build run off of first card in hand
	//	Card runStart = hand.front();

	//	// flag to track if run is valid
	//	bool isRun = true;

	//	// look at all cards following runStart
	//	for (int cmpIdx = 1; cmpIdx < hand.size(); cmpIdx++) {
	//		// jokers/wildcards are coolio
	//		if (hand.at(cmpIdx).isJoker() || hand.at(cmpIdx).isWildcard()) {
	//			continue;
	//		}

	//		// match suit and face should be start.face + cmpIdx
	//		if (hand.at(cmpIdx).getSuit() == runStart.getSuit()
	//			&& hand.at(cmpIdx).getFace() == runStart.getFace() + cmpIdx) {
	//			continue;
	//		}

	//		// use joker/wildcard if possible
	//		if (totalWilds > 0) {
	//			totalWilds--;
	//			continue;
	//		}

	//		// hand did not pass tests
	//		isRun = false;
	//	}

	//	// check if flag has been broken
	//	if (isRun) {
	//		return true;
	//	}

	//	// cards did not pass test, look at next permutation
	////} while (std::next_permutation(begin(hand), end(hand), compareCards()));

	//// no permutations passed the test
	//return false;
}

/* *********************************************************************
Function Name: isBook
Purpose: Determine if the given cards are a valid book
Parameters:
	vector<Card> hand the list of cards to check
Return Value:
	true if the given cards are a valid book
Assistance Received: None
********************************************************************* */
bool Assembler::isBook(vector<Card> hand) {
	// books must be 3 Cards or longer
	if (hand.size() < 3) {
		return false;
	}

	// set the face to match
	int face = hand.front().getFace();

	// check if first card is joker/wildcard
	for (int i = 0; i < hand.size() - 1; i++) {
		if (hand.at(i).isJoker() || hand.at(i).isWildcard()) {
			face = hand.at(i + 1).getFace();
		}
		else {
			break;
		}
	}

	// check if all Cards have the same face
	for (int i = 1; i < hand.size(); i++) {
		if (hand.at(i).getFace() != face) {
			// jokers and wildcards continue books
			if (hand.at(i).isJoker() || hand.at(i).isWildcard()) {
				continue;
			}
			else {
				return false;
			}
		}
	}

	// book has not broken
	return true;
}

/** *********************************************************************
Function Name: sortHandByFace
Purpose: Sort the given hand by face
Parameters:
	const vector<Card> inHand the hand to sort
Return Value:
	vector<Card> the sorted hand
Assistance Received: https://www.geeksforgeeks.org/bubble-sort/
********************************************************************* */
vector<Card> Assembler::sortHandByFace(const vector<Card> inHand) {
	if (inHand.size() == 0) {
		return vector<Card>();
	}

	vector<Card> hand = vector<Card>(inHand);

	// bubble sort the hand by face (ascending)
	for (int i = 0; i < hand.size() - 1; i++) {
		for (int j = 0; j < hand.size() - i - 1; j++) {
			// swap Cards if current Card is greater than next Card
			// or current Card is Joker
			if (hand.at(j).getFace() > hand.at(j + 1).getFace()
				|| hand.at(j).isJoker()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
		}
	}

	// bubble sort jokers by suit
	for (int i = 0; i < hand.size() - 1; i++) {
		for (int j = 0; j < hand.size() - i - 1; j++) {
			// if cards are both jokers, sort by suit ascending
			if (hand.at(j).isJoker() && hand.at(j + 1).isJoker() && hand.at(j).getSuit() > hand.at(j + 1).getSuit()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
		}
	}

	return hand;
}

/** *********************************************************************
 Function Name: sortHandBySuit
 Purpose: Sort the Computer's hand by suit then face
 Parameters:
	const vector<Card> inHand the hand to sort
 Return Value:
	vector<Card> the sorted hand
 Assistance Received: https://www.geeksforgeeks.org/bubble-sort/
 ********************************************************************* */
vector<Card> Assembler::sortHandBySuit(const vector<Card> inHand) {
	if (inHand.size() == 0) {
		return vector<Card>();
	}

	vector<Card> hand = vector<Card>(inHand);

	// bubble sort the hand by suit (ascending)
	for (int i = 0; i < hand.size() - 1; i++) {
		for (int j = 0; j < hand.size() - i - 1; j++) {
			// swap Cards if
			//	current Card is Joker
			//	OR current Card suit is greater than next Card suit
			//	OR suits are same and current Card face is greater than next Card face
			if (hand.at(j).isJoker()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
			else if (hand.at(j).getSuit() > hand.at(j + 1).getSuit()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
			else if (hand.at(j).getSuit() == hand.at(j + 1).getSuit()
				&& hand.at(j).getFace() > hand.at(j + 1).getFace()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
		}
	}

	// bubble sort jokers by suit
	for (int i = 0; i < hand.size() - 1; i++) {
		for (int j = 0; j < hand.size() - i - 1; j++) {
			// if cards are both jokers, sort by suit ascending
			if (hand.at(j).isJoker() && hand.at(j + 1).isJoker() && hand.at(j).getSuit() > hand.at(j + 1).getSuit()) {
				std::swap(hand.at(j), hand.at(j + 1));
			}
		}
	}

	return hand;
}

//// https://leetcode.com/problems/next-permutation/solution/
//vector<Card> Assembler::next_permutation(const vector<Card> hand) {
//	// find first pair of cards from the end that need to be swapped
//	int i = hand.size() - 2;
//	while (i >= 0 && hand.at(i + 1) <= hand.at(i)) {
//		i--;
//	}
//
//	if (i >= 0) {
//		int j = hand.size() - -1;
//		while (j >= 0 && hand.at(j) <= hand.at(i)) {
//			j--;
//		}
//		std::swap(hand.at(i), hand.at(j));
//	}
//
//	return hand;
//}
//
//vector<Card> Assembler::reverse(const vector<Card> inHand, int start) {
//	vector<Card> hand = vector<Card>(inHand);
//	int i = start, j = hand.size() - 1;
//	while (i < j) {
//		std::swap(hand.at(i), hand.at(j));
//		i++;
//		j--;
//	}
//
//	return hand;
//}