#include "othello.h"

Othello::Othello(Board &board, Controller &player1, Controller &player2) : BoardLogic(board), black(player1), white(player2) {
	setTile(WHITE, 3, 4);
	setTile(WHITE, 4, 3);
	setTile(BLACK, 3, 3);
	setTile(BLACK, 4, 4);
	if (player1.side == WHITE) {
		black = player2;
		white = player1;
	}
}

bool Othello::playTurn() {
	bool gameEnd = false;
	// User's turn
	if (isThereValidMove(black.side)) {
		while (true) {
			Controller::MoveType move = black.getNewMove(board);
			if (move == Controller::MOVE)
				break;
			else if (move == Controller::INVALID)
				cout << "Invalid Move" << endl;
			else
				return false;
		}
		this->board.printBoard();
	}
	else {
		cout << "No valid move available" << endl;
		gameEnd = true;
	}
	if (isThereValidMove(white.side)) {
		while (true) {
			Controller::MoveType move = white.getNewMove(board);
			if (move == Controller::MOVE)
				break;
			else if (move == Controller::INVALID)
				cout << "Invalid Move" << endl;
			else
				return false;
		}
		this->board.printBoard();
	}
	else {
		cout << "No valid move available" << endl;
		if (gameEnd) {
			cout << "The End" << endl;
			return false;
		}
	}
	return true;
}