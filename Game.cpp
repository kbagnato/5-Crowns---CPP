#include "Game.h"

/* *********************************************************************
Function Name: Game
Purpose: Game constructor
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Game::Game() {
	m_roundNum = 1;
	m_nextPlayerIdx = 0;
	m_human = Human();
	m_computer = Computer();
}


/* *********************************************************************
Function Name: play
Purpose: Step the Players through the Game
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void Game::play() {
	// play through every round
	while (m_roundNum <= MAX_ROUND) {
		Round round(m_roundNum, m_nextPlayerIdx, &m_human, &m_computer);
		round.play();

		// get stats at end of round (for serialization)
		m_roundNum = round.getRoundNum();
		m_roundNum++;
		m_nextPlayerIdx = round.getNextPlayerIdx();

		// clear player's hands after round
		m_human.clearHand();
		m_computer.clearHand();
	}

	// print winner
	if (m_human.getScore() > m_computer.getScore()) {
		cout << "Congrats, you win!" << endl;
	}
	else if (m_computer.getScore() > m_human.getScore()) {
		cout << "Sorry, you lose." << endl;
	}
	else {
		cout << "Amazing, it's a tie!" << endl;
	}
}
