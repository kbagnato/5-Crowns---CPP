#include <iostream>
using namespace std;

#include "Card.h"
#include "Deck.h"
#include "CardDealer.h"
#include "Player.h"
#include "Round.h"
#include "Computer.h"
#include "Game.h"
#include "Assembler.h"

int main() {
	cout << "Five Crowns by Kevin Bagnato" << endl;

	/** testing Card constuctors*/ {
		//Card c1;
		//cout << c1.toString() << endl;
		//Card c2(2, 'H');
		//cout << c2.toString() << endl;
		//Card c3(5, 'G');
		//cout << c3.toString() << endl;
		//Card c4(5, 'T');
		//cout << c4.toString() << endl;
		/** test Card copy, wildcard */
		//Card c5(3, 'S');
		//Card c6 = c5;
		//c5.setFace(8);
		//c5.updateWildcard(8);
		//cout << c5.toString() << " is " << (c5.isWildcard() ? "" : "not " ) << "wild" << endl;
		//cout << c6.toString() << " is " << (c6.isWildcard() ? "" : "not ") << "wild" << endl;
		/** test Card joker */
		//Card joker(11, '1');
		//cout << joker.toString() << " is " << (joker.isJoker() ? "" : "not ") << "a joker" << endl;
		//cout << c5.toString() << " is " << (c5.isJoker() ? "" : "not ") << "a joker" << endl;
	}

	/** testing deck */ {
		//Deck d1;
		////cout << d1.toString() << endl;
		////cout << d1.isEmpty() << endl;
		//Card newCard = d1.dealCard();
		//cout << newCard.toString() << endl;
	}

	/** test CardDealer */ {
		//CardDealer cardDealer;
		//cout << cardDealer.toString() << endl;
		//for (int i = 0; i < 20; i++) {
		//	cout << cardDealer.dealCard().toString() << " " << endl;
		//}
		//cout << cardDealer.toString() << endl;
	}

	/** test Player */ {
		//Deck deck;
		//Player player;

		//cout << "Deck: " << deck.toString();
		//for (int count = 0; count < 8; count++) {
		//	player.addCard(deck.dealCard());
		//}
		//cout << "Player: " << player.handToString();
		//cout << "Deck: " << deck.toString();
	}

	/** test Round */ {
		//Human human;
		//Computer computer;
		//Round round(1, &human, &computer);
		//round.play();
	}

	/** test Player::isBook() */ {
		//vector<Card> h1;
		//h1.push_back(Card(3, 'H'));
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//// is a book
		//cout << "is " << (Player::isBook(h1) ? "" : "not ") << "a book." << endl;

		//h1.push_back(Card(4, 'H'));
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));

		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//// not a book because 4
		//cout << "is " << (Player::isBook(h1) ? "" : "not ") << "a book." << endl;

		//// can't use shorthand loop for some reason. perhaps it makes a copy of card?
		//for (int i = 0; i < h1.size(); i++) {
		//	h1.at(i).updateWildcard(4);
		//	cout << h1.at(i).toString() << (h1.at(i).isWildcard() ? "* " : " ");
		//}
		//// is a book with 4 as wildcard
		//cout << "is " << (Player::isBook(h1) ? "" : "not ") << "a book." << endl;

		//// test jokers
		//vector<Card> h2;
		//h2.push_back(Card(3, 'H'));
		//h2.push_back(Card(3, 'D'));
		//h2.push_back(Card(11, '3'));
		//for (Card card : h2) {
		//	cout << card.toString() << " ";
		//}
		//// is a book
		//cout << "is " << (Player::isBook(h2) ? "" : "not ") << "a book." << endl;
	}

	/** test Player::isRun() */ {
		//vector<Card> run1;
		//run1.push_back(Card(3, 'D'));
		//run1.push_back(Card(4, 'D'));
		//run1.push_back(Card(5, 'D'));
		//for (Card card : run1) {
		//	cout << card.toString() << " ";
		//}
		//// good run
		//cout << "is " << (Player::isRun(run1) ? "" : "not ") << "a run." << endl;

		//// break the run
		//run1.push_back(Card(6, 'T'));
		//for (Card card : run1) {
		//	cout << card.toString() << " ";
		//}
		//// not a run
		//cout << "is " << (Player::isRun(run1) ? "" : "not ") << "a run." << endl;

		//// make it okay by turning 6 wild
		//for (int i = 0; i < run1.size(); i++) {
		//	run1.at(i).updateWildcard(6);
		//	cout << run1.at(i).toString() << (run1.at(i).isWildcard() ? "* " : " ");
		//}
		//// good run
		//cout << "is " << (Player::isRun(run1) ? "" : "not ") << "a run." << endl;
		//
		//// add joker
		//run1.push_back(Card(11, '1'));
		//for (Card card : run1) {
		//	cout << card.toString() << " ";
		//}
		//cout << "is " << (Player::isRun(run1) ? "" : "not ") << "a run." << endl;
	}

	/** test Player::removeAllBooks() */ {
		//vector<Card> h1;
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));
		//h1.push_back(Card(3, 'H'));
		//h1.push_back(Card(4, 'D'));
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//vector<Card> h2 = Player::removeAllBooks(h1);
		//for (Card card : h2) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;
	}
	{
		//vector<Card> h1;
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));
		//h1.push_back(Card(3, 'H'));
		//h1.push_back(Card(4, 'D'));
		//h1.push_back(Card(5, 'D'));
		//h1.push_back(Card(5, 'H'));
		//h1.push_back(Card(5, 'T'));
		//h1.push_back(Card(5, 'D'));
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//vector<Card> h2 = Player::removeAllBooks(h1);
		//for (Card card : h2) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;
	}

	/** test removeAllBooks */ {
		//vector<Card> h1;
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));
		//h1.push_back(Card(3, 'H'));
		//h1.push_back(Card(4, 'D'));
		//h1.push_back(Card(5, 'D'));
		//h1.push_back(Card(5, 'D'));
		//cout << "Original hand: ";
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//vector<vector<Card>> booksRemoved = Player::removeAllBooks(h1);
		//cout << "After removal: ";
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//cout << "Books removed: " << endl;
		//for (vector<Card> book : booksRemoved) {
		//	for (Card card : book) {
		//		cout << card.toString() << " ";
		//	}
		//	cout << endl;
		//}
	}

	/** test removeAllRuns*/
	{
		//vector<Card> h1;
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(4, 'D'));
		//h1.push_back(Card(5, 'D'));
		//h1.push_back(Card(6, 'D'));
		//h1.push_back(Card(7, 'T'));
		//h1.push_back(Card(8, 'T'));
		//h1.push_back(Card(9, 'T'));
		//h1.push_back(Card(8, 'T'));
		//h1.push_back(Card(11, 'T'));
		//h1.push_back(Card(11, '1'));
		//h1.push_back(Card(13, 'T'));
		//cout << "Original hand: ";
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//vector<vector<Card>> runsRemoved = Player::removeAllRuns(h1);
		//cout << "After removal: ";
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;

		//cout << "Books removed: " << endl;
		//for (vector<Card> book : runsRemoved) {
		//	for (Card card : book) {
		//		cout << card.toString() << " ";
		//	}
		//	cout << endl;
		//}
	}

	/** test goOut */ {
		//Player p1;
		//// will not go out
		//vector<Card> h1;
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(3, 'T'));
		//h1.push_back(Card(3, 'H'));
		//h1.push_back(Card(4, 'D'));
		//h1.push_back(Card(5, 'D'));
		//h1.push_back(Card(5, 'D'));
		//h1.push_back(Card(3, 'D'));
		//h1.push_back(Card(4, 'D'));
		//h1.push_back(Card(5, 'D'));
		//p1.setHand(h1);
		//for (Card card : h1) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;
		//p1.goOut();
		//cout << "-----------------"<<endl;
		//cout << endl;

		//// should go out using wildcard
		//vector<Card> h2;
		//h2.push_back(Card(3, 'T'));
		//h2.push_back(Card(4, 'T'));
		//h2.push_back(Card(5, 'T'));
		//h2.push_back(Card(6, 'T'));
		//h2.push_back(Card(3, 'C').updateWildcard(3));
		//h2.push_back(Card(8, 'T'));
		//p1.setHand(h2);
		//for (Card card : h2) {
		//	cout << card.toString() << " ";
		//}
		//cout << endl;
		//p1.goOut();
	}

	/** test load */ {
		//Human human;
		//Computer computer;
		//Round round(1, &human, &computer);
		//round.load("C:\\Users\\kdawg\\Desktop\\Ramapo\\OPL\\serial4.txt");
		//round.play();
	}

	/** test Assembler */
	//vector<Card> hand;
	//hand.push_back(Card(5, 'H'));
	//hand.push_back(Card(3, 'H'));
	//hand.push_back(Card(4, 'H'));
	//hand.push_back(Card(5, 'C'));
	//hand.push_back(Card(4, 'H'));
	//hand.push_back(Card(11, '1'));
	//hand.push_back(Card(5, 'H'));
	//for (Card card : hand) {
	//	cout << card.toString() << " ";
	//}
	//
	//cout << endl;
	//vector<Card> cheap = Assembler::getCheapestHand(hand);
	//for (Card card : cheap) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl << endl;
	////cout << endl << "--------------------------" << endl << endl;

	///* add duplicate cards to current hand and check again */
	//hand.push_back(Card(5, 'H'));
	//hand.push_back(Card(4, 'H'));
	//for (Card card : hand) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl;
	//vector<Card> cheap2 = Assembler::getCheapestHand(hand);
	//for (Card card : cheap2) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl << endl;	//cout << endl << "--------------------------" << endl << endl;

	///** check remaining cards matches best assembly */
	//vector<Card> reamining = Assembler::getCheapestAssembly(Assembler(hand), Assembler()).getRemainingCards();
	//for (Card card : reamining) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl << endl;
	////cout << endl << "--------------------------" << endl << endl;

	///** test getCheapest Hand with small hand */
	//vector<Card> hand2;
	//hand2.push_back(Card(5, 'H'));
	//hand2.push_back(Card(3, 'H'));
	//hand2.push_back(Card(4, 'T'));
	//for (Card card : hand2) {
	//	cout << card.toString() << " ";
	//}

	//cout << endl;
	//vector<Card> cheap3 = Assembler::getCheapestHand(hand2);
	//for (Card card : cheap3) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl << endl;

	//	//cout << endl << "--------------------------" << endl << endl;
	///** J1 KC QC */
	//vector<Card> bruh;
	//bruh.push_back(Card(11, '1'));
	//bruh.push_back(Card(13, 'C'));
	//bruh.push_back(Card(12, 'C'));
	//cout << "Hand to check: " << endl;
	//for (Card card : bruh) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(bruh), Assembler()).toString() << endl;
	//cout << endl << "--------------------------" << endl << endl;

	///** J1 KC KT */
	//bruh.clear();
	//bruh.push_back(Card(11, '1'));
	//bruh.push_back(Card(13, 'C'));
	//bruh.push_back(Card(13, 'T'));
	//cout << "Hand to check: " << endl;
	//for (Card card : bruh) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(bruh), Assembler()).toString() << endl;

	//cout << endl << "--------------------------" << endl << endl;

	//vector<Card> case1;
	//case1.push_back(Card(6, 'T'));
	//case1.push_back(Card(7, 'T'));
	//case1.push_back(Card(8, 'T'));
	//cout << "Hand to check: ";
	//for (Card card : case1) {
	//	cout << card.toString() << (card.isWildcard() ? "*" : "") << " ";
	//}
	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(case1), Assembler()).toString() << endl;
	////cout << endl << "--------------------------" << endl << endl;

	//case1.clear() ;
	//case1.push_back(Card(5, 'T'));
	//case1.push_back(Card(4, 'C').updateWildcard(4));
	//case1.push_back(Card(7, 'T'));
	//case1.push_back(Card(8, 'T'));
	//for (Card card : case1) {
	//	cout << card.toString() << (card.isWildcard() ? "*" : "") << " ";
	//}
	//cout << endl;

	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(case1), Assembler()).toString() << endl;

	//cout << endl << "--------------------------" << endl << endl;

	///** test 5T 7T 8T 4C (the biggest child in the next test) */
	//case1.clear();
	//case1.push_back(Card(5, 'T'));
	//case1.push_back(Card(7, 'T'));
	//case1.push_back(Card(8, 'T'));
	//case1.push_back(Card(4, 'C').updateWildcard(4));
	//for (Card card : case1) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(case1), Assembler()).toString() << endl << endl;;

	//cout << endl << "--------------------------" << endl << endl;

	/////** test 5T 7T 8T 4C 8D (the user's result at the end of case 1) */
	//case1.clear();
	//case1.push_back(Card(5, 'T'));
	//case1.push_back(Card(7, 'T'));
	//case1.push_back(Card(8, 'T'));
	//case1.push_back(Card(4, 'C').updateWildcard(4));
	//case1.push_back(Card(8, 'D'));
	//for (Card card : case1) {
	//	cout << card.toString() << " ";
	//}
	//cout << endl;
	//cout << Assembler::getCheapestAssembly(Assembler(case1), Assembler()).toString() << endl;
	//cout << endl << "--------------------------" << endl << endl;

	///** test */ {
	//	vector<Card> case1;
	//	case1.push_back(Card(6, 'T'));
	//	case1.push_back(Card(7, 'D'));
	//	case1.push_back(Card(8, 'T'));
	//	cout << "Hand to check: ";
	//	for (Card card : case1) {
	//		cout << card.toString() << (card.isWildcard() ? "*" : "") << " ";
	//	}
	//	cout << endl;
	//	cout << Assembler::getCheapestAssembly(Assembler(case1), Assembler()).toString() << endl;
	//}

	//cout << endl << "--------------------------" << endl << endl;
	//// TODO this hand should suggest the 8D
	///** test helpDiscard */ {
	//	vector<Card> testHelpDiscard;
	//	testHelpDiscard.push_back(Card(5, 'T'));
	//	testHelpDiscard.push_back(Card(8, 'D'));
	//	testHelpDiscard.push_back(Card(7, 'T'));
	//	testHelpDiscard.push_back(Card(8, 'T'));
	//	testHelpDiscard.push_back(Card(4, 'C').updateWildcard(4));

	//	cout << Assembler::getCheapestAssembly(Assembler(testHelpDiscard), Assembler()).toString() << endl;


	//	Player p;
	//	p.setHand(testHelpDiscard);
	//	string reason;
	//	Card choice = p.helpDiscard(reason);

	//cout << endl << "--------------------------" << endl << endl;
	//	cout << choice.toString() << " because " + reason << endl;
	//}

	vector<Card> hand;
	/*hand.push_back(Card(9, 'D'));
	hand.push_back(Card(9, 'C'));
	hand.push_back(Card(9, 'H'));
	hand.push_back(Card(4, 'H').updateWildcard(4));
	cout << Assembler::isBook(hand) << endl;
*/
	//hand.push_back(Card(5, 'T'));
	//hand.push_back(Card(8, 'T'));
	//hand.push_back(Card(7, 'T'));
	//hand.push_back(Card(4, 'H').updateWildcard(4));
	//cout << Assembler::isRun(hand) << endl;



	///** test Game */
	{
		Game g;
		g.play();
	}


		//cout << endl << "--------------------------" << endl << endl;

	///** test operator overload */
	//cout << true << endl;
	//
	//Card c3(5, 'D');
	//Card c1(4, 'T');
	//Card c2(4, 'D');

	//cout << (c1 <= c3) << endl;
	//cout << (c2 <= c3) << endl;
	//cout << (c3 <= c2) << endl << endl;
	//
	//
	//cout << (c1 <= c1) << endl;
	//cout << (c3 <= c2) << endl;
	//cout << (c3 <= c1) << endl;
	//
	//cout << endl << "--------------------------" << endl << endl;

	//hand.clear();
	//hand.push_back(c1);
	//hand.push_back(c2);
	//hand.push_back(c3);

	//// test sort
	//sort(hand.begin(), hand.end());

	//for (Card card : hand) {
	//	cout << card.toString() << " ";
	//}

	system("pause");
	return 0;
}