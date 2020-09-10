#include "Round.h"

const int Round::TOTAL_PLAYERS = 2;

/* *********************************************************************
Function Name: Round
Purpose: Round constructor
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Round::Round() {
	m_roundNum = 1;
	m_playerVector = vector<Player*>(TOTAL_PLAYERS);

	m_cardDealer = CardDealer();

	m_drawPile = vector<Card>();
	m_discardPile = vector<Card>();
}

/* *********************************************************************
Function Name: Round
Purpose: Round constructor
Parameters:
	int inRoundNum the current round number
	Player inHuman the Human Player
	Player inComputer the Computer Player
Return Value: None
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
Round::Round(int inRoundNum, int inNextPlayerIdx, Human* inHuman, Computer* inComputer) {
	// set local copy of round number and next player index
	m_roundNum = inRoundNum;
	m_nextPlayerIdx = inNextPlayerIdx;

	// create Players vector
	m_playerVector = vector<Player*>();
	m_playerVector.push_back(inHuman);
	m_playerVector.push_back(inComputer);

	// update wild cards
	m_cardDealer = CardDealer();
	m_cardDealer.updateWildcards(m_roundNum + 2);

	// deal cards to players
	for (int count = 0; count < m_roundNum + 2; count++) {
		for (int playerIndex = 0; playerIndex < TOTAL_PLAYERS; playerIndex++) {
			m_playerVector[playerIndex]->addCard(m_cardDealer.dealCard());
		}
	}

	// deal rest of cards to DrawPile
	m_drawPile = vector<Card>();
	Card nextCard = m_cardDealer.dealCard();
	while (nextCard.getFace() != 0 && nextCard.getSuit() != 'X') {
		// add card to top of draw pile
		m_drawPile.insert(m_drawPile.begin(), nextCard);
		nextCard = m_cardDealer.dealCard();
	}

	// move top card from drawPile to discardPile
	m_discardPile = vector<Card>();
	m_discardPile.insert(m_discardPile.begin(), m_drawPile.front());
	m_drawPile.erase(m_drawPile.begin());
}

/* *********************************************************************
Function Name: toString
Purpose: Nicely format the Round
Parameters: None
Return Value: The Round as a string
Assistance Received: Dr. Kumar's Sunday lecture
********************************************************************* */
void Round::printRound() {
	// print round number
	cout << "Round: " << m_roundNum << endl;
	
	// add human hand and score
	cout << "Computer:\n\tScore: " << m_playerVector[1]->getScore() << "\n\t"
		<< "Hand: " << m_playerVector[1]->handToString() << endl;

	// add computer hand and score
	cout << "Player:\n\tScore: " << m_playerVector[0]->getScore() << "\n\t"
		<< "Hand: " << m_playerVector[0]->handToString() << endl;

	// add draw pile
	cout << "Draw Pile: ";
	for (Card card : m_drawPile) {
		cout << card.toString() << " ";
	}
	cout << endl;

	// add discard pile
	cout << "Discard Pile: ";
	for (Card card : m_discardPile) {
		cout << card.toString() << " ";
	}
	cout << endl;

	cout << "Next Player: ";
	if (m_nextPlayerIdx == 0) {
		cout << "Human\n";
	}
	else {
		cout << "Computer\n";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: play
Purpose: Play through a round
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::play() {
	if (m_roundNum == 1) {
		coinToss();
	}

	// alternate players until one goes out 
	while (true) {
		// print the current round statss
		printRound();

		// ask the user to save/load
		serialize();

		// nextPlayer will play and return true if Player goes out
		if (m_playerVector[m_nextPlayerIdx]->play(m_drawPile, m_discardPile) == 0) {
			// set index to next Player
			m_nextPlayerIdx = (m_nextPlayerIdx + 1) % TOTAL_PLAYERS;
			break;
		}

		// set index to next Player
		m_nextPlayerIdx = (m_nextPlayerIdx + 1) % TOTAL_PLAYERS;
	}

	// print round last time
	cout << "The round loser can make one last move..." << endl << endl;
	printRound();

	// have other player play once and add to their score
	int pointsEarned = m_playerVector[m_nextPlayerIdx]->lastMove(m_drawPile, m_discardPile);
	m_playerVector[m_nextPlayerIdx]->addToScore(pointsEarned);

	// print loser's points earned
	cout << (m_nextPlayerIdx == 0 ? "You" : "The computer") << " lost the round and earned " << pointsEarned << " points." << endl;
	cout << "End of Round " << m_roundNum << "." << endl << endl;

	// increment nextPlayerIdx
	m_nextPlayerIdx = (m_nextPlayerIdx + 1) % TOTAL_PLAYERS;
}

/* *********************************************************************
Function Name: getNextPlayerIdx
Purpose: Return the next Player index
Parameters: None
Return Value:
	int the next Player index
Assistance Received: None
********************************************************************* */
int Round::getNextPlayerIdx() {
	return m_nextPlayerIdx;
}

/* *********************************************************************
Function Name: getRoundNum
Purpose: Return the round number
Parameters: None
Return Value:
	int the current round number
Assistance Received: None
********************************************************************* */
int Round::getRoundNum() {
	return m_roundNum;
}

/* *********************************************************************
Function Name: setNextPlayerIdx
Purpose: Set the next Player index
Parameters:
	const int inNextPlayerIdx the next Player index to set
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::setNextPlayerIdx(const int inNextPlayerIdx) {
	if (inNextPlayerIdx < TOTAL_PLAYERS) {
		m_nextPlayerIdx = inNextPlayerIdx;
	}
}

/* *********************************************************************
Function Name: serialize
Purpose: Ask the user if they want to serialize
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::serialize() {
	// ask user if they want to serialize
	string input;
	do {
		cout << "Do you want to serialize? (Yes / No): ";
		cin >> input;
	} while (!(input.compare("Yes") == 0 || input.compare("No") == 0));

	// begin serialization
	if (input.compare("Yes") == 0) {
		
		// get file location
		string file;
		cout << "Enter the file location: ";
		cin >> file;

		// ask user to save or load
		do {
			cout << "Do you want to save or load? (Save / Load): ";
			cin >> input;
		} while (!(input.compare("Save") == 0 || input.compare("Load") == 0));
		cout << endl;

		if (input.compare("Save") == 0) {
			// file location
			save(file);
		}
		else {
			// get file location
			load(file);
		}
	}
	else {
		cout << endl;
	}
}

/* *********************************************************************
Function Name: save
Purpose: Save the current Round stats to a serialization file
Parameters:
	string fileLoc - the address of the file
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::save(string fileLoc) {
	
	// create file at given path
	ofstream saveFile;
	saveFile.open(fileLoc);

	// create string for draw pile
	string drawStr = "";
	for (Card card : m_drawPile) {
		drawStr += card.toString() + " ";
	}

	// create string for discard pile
	string discardStr = "";
	for (Card card : m_discardPile) {
		discardStr += card.toString() + " ";
	}

	// write details to file
	saveFile << "Round: " << m_roundNum << "\n\n";
	saveFile << "Computer:\n\tScore: " << m_playerVector.at(1)->getScore() << "\n\t"
		"Hand: " << m_playerVector.at(1)->handToString() << "\n\n";
	saveFile << "Human:\n\tScore: " << m_playerVector.at(0)->getScore() << "\n\t"
		"Hand: " << m_playerVector.at(0)->handToString() << "\n\n";
	saveFile << "Draw Pile: " << drawStr << "\n\n";
	saveFile << "Discard Pile: " << discardStr << "\n\n";
	saveFile << "Next Player: " << (m_nextPlayerIdx ? "Computer" : "Human\n");

	saveFile.close();

	cout << "Goodbye!" << endl;
	system("pause");
	exit(0);
}

/* *********************************************************************
Function Name: load
Purpose: Read a serialization file and update the Round appropriately
Parameters:
	string fileLoc - the address of the file
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::load(string fileLoc) {
	// data to capture from file
	int inRoundNum = 0;
	int inCpuScore = 0;
	string cpuHand;
	int inHumScore = 0;
	string humHand;
	string draw, discard;
	string inNextPlayer;
	bool inHumanNext = true;

	// open file
	ifstream inFile(fileLoc);
	if (inFile.is_open()) {
		string line;

		// read file line by line
		while (getline(inFile, line)) {
			// get round number
			if (line.find("Round:") != string::npos) {
				inRoundNum = std::stoi(line.substr(line.find(':') + 2));
			}
			// get computer score and hand
			else if (line.find("Computer:") != string::npos) {
				while (getline(inFile, line)) {
					if (line.find("Score:") != string::npos) {
						inCpuScore = std::stoi(line.substr(line.find(':') + 2));
					}
					if (line.find("Hand:") != string::npos) {
						cpuHand = line.substr(line.find(':') + 2);
						break;
					}
				}
			}
			// get human score and hand
			else if (line.find("Human:") != string::npos) {
				while (getline(inFile, line)) {
					if (line.find("Score:") != string::npos) {
						inHumScore = std::stoi(line.substr(line.find(':') + 2));
					}
					if (line.find("Hand:") != string::npos) {
						humHand = line.substr(line.find(':') + 2);
						break;
					}
				}
			}
			// get draw pile
			else if (line.find("Draw Pile: ") != string::npos) {
				draw = line.substr(line.find(':') + 2);
			}
			// get discard pile
			else if (line.find("Discard Pile: ") != string::npos) {
				discard = line.substr(line.find(':') + 2);
			}
			// get if nextPlayer is Human or Computer
			else if (line.find("Next Player: ") != string::npos) {
				inNextPlayer = line.substr(line.find(':') + 2);
				inHumanNext = inNextPlayer.find("Human") ? false : true;
			}

		}

		inFile.close();
	}

	// update round number
	m_roundNum = inRoundNum;

	// create Player's Cards from string with proper wildcard status
	vector<Card> h = stringToVector(humHand);
	for (int i = 0; i < h.size(); i++) {
		h.at(i).updateWildcard(m_roundNum + 2);
	}
	vector<Card> c = stringToVector(cpuHand);
	for (int i = 0; i < c.size(); i++) {
		c.at(i).updateWildcard(m_roundNum + 2);
	}

	// update Player's data
	m_playerVector.at(0)->setScore(inHumScore);
	m_playerVector.at(0)->setHand(h);
	m_playerVector.at(1)->setScore(inCpuScore);
	m_playerVector.at(1)->setHand(c);

	// create Card piles from strings with proper wildcard status
	vector<Card> inDrawPile = stringToVector(draw);
	for (int i = 0; i < inDrawPile.size(); i++) {
		inDrawPile.at(i).updateWildcard(m_roundNum + 2);
	}
	vector<Card> inDiscardPile = stringToVector(discard);
	for (int i = 0; i < inDiscardPile.size(); i++) {
		inDiscardPile.at(i).updateWildcard(m_roundNum + 2);
	}

	// update piles
	m_drawPile.clear();
	m_drawPile = inDrawPile;
	m_discardPile.clear();
	m_discardPile = inDiscardPile;

	// update next player index
	inHumanNext ? m_nextPlayerIdx = 0 : m_nextPlayerIdx = 1;

	// print new round data
	printRound();
}

/* *********************************************************************
Function Name: stringToVector
Purpose: Parse a given string into a vector of Cards
Parameters:
	string cards - a string representing a list of Cards
Return Value: 
	vector<Card> the hand of given Cards
Assistance Received:
	https://docs.microsoft.com/en-us/visualstudio/code-quality/c26451
********************************************************************* */
vector<Card> Round::stringToVector(const string inCards) {
	string cards = inCards;
	
	// trim whitespace from front
	while (cards[0] == ' ') {
		cards = cards.substr(1);
	}

	// parse string to Cards and add to vector
	int tempFace;
	char tempSuit;
	vector<Card> hand;
	for (int i = 0; i < cards.size(); i += 3) {
		switch (cards[i]) {
		case 'X':
			tempFace = 10;
			break;
		case 'J':
			tempFace = 11;
			break;
		case 'Q':
			tempFace = 12;
			break;
		case 'K':
			tempFace = 13;
			break;
		case ' ':
			continue;
		default:
			tempFace = cards[i] - '0';
		}
		tempSuit = cards[i + (__int64)1]; // C26451 reported here without cast
		if (tempFace != ' ') {
			hand.push_back(Card(tempFace, tempSuit));
		}
	}

	// return Card list
	return hand;
}

/* *********************************************************************
Function Name: coinToss
Purpose: Let the user call a random coin toss to determine who begins
	the round
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Round::coinToss() {
	// get call from user
	string input;
	do {
		cout << "Call the coin toss (Heads / Tails): ";
		cin >> input;
	} while (!(input.compare("Heads") == 0 || input.compare("heads") == 0
		|| input.compare("Tails") == 0 || input.compare("tails") == 0));

	// randomly fip coin
	int flip = rand() % 2;
	cout << "The coin landed on " << (flip ? "Heads" : "Tails") << "." << endl;

	// check if user was correct
	if (flip == 1 && input.compare("Heads") == 0 || input.compare("heads") == 0) {
		cout << "You go first!" << endl;
		m_nextPlayerIdx = 0;
	}
	else {
		cout << "The computer goes first." << endl;
		m_nextPlayerIdx = 1;
	}

	cout << endl;
}
