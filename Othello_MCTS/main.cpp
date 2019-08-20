#include "mcts.h"
#include "othello.h"
#include "string"

int main() {
	bool userPlay = false;
	cout << "\t\t\tMenu\t\t\t" << endl;
	cout << "1. Player vs Computer" << endl;
	cout << "2. Computer vs Computer" << endl << endl << endl;
	while (true) {
		string selection;
		cout << "Select: ";
		cin >> selection;
		if (selection.size() == 1) {
			if (selection[0] == '1') {
				userPlay = true;
				break;
			}
			else if (selection[0] == '2')
				break;
		}
	}

	if (userPlay) {
		UserController user;
		Disc userSide;
		cout << endl << endl;
		cout << "1. BLACK" << endl;
		cout << "2. WHITE" << endl << endl << endl;
		while (true) {
			cout << "Select your side: ";
			string selection;
			cin >> selection;
			if (selection.size() == 1) {
				if (selection[0] == '1') {
					user.setSide(BLACK);
					userSide = BLACK;
					break;
				}
				else if (selection[0] == '2') {
					userSide = WHITE;
					user.setSide(WHITE);
					break;
				}
			}
		}
		ComputerController computer(getOpponent(userSide));
		cout << endl << endl;
		cout << "Computer Difficulty" << endl << endl;
		cout << "1. No Heuristic" << endl;
		cout << "2. Heuristic" << endl;
		while (true) {
			cout << "Select: ";
			string selection;
			cin >> selection;
			if (selection.size() == 1) {
				if (selection[0] == '1')
					break;
				else if (selection[0] == '2') {
					computer.useHeuristic();
					break;
				}
			}
		}
		Board board;
		Disc winner;
		if (userSide == BLACK) {
			Othello game(board, user, computer);
			winner = game.run();
		}
		else if (userSide == WHITE){
			Othello game(board, computer, user);
			winner = game.run();
		}
		cout << "Winner is: " << winner << endl;
	}
	else {
		cout << endl << endl;
		cout << "MCTS without heuristic (Black) will play against MCTS with heuristic (White)" << endl << endl;;
		cout << "Select the number of simulation" << endl << endl;
		cout << "1. 1" << endl;
		cout << "2. 100" << endl << endl;
		int num;
		while (true) {
			cout << "Select: ";
			string selection;
			cin >> selection;
			if (selection.size() == 1) {
				if (selection[0] == '1') {
					num = 1;
					break;
				}
				else if (selection[0] == '2') {
					num = 100;
					break;
				}
			}
		}
		ComputerController user(BLACK, false);
		ComputerController computer(WHITE, true);
		int black = 0, white = 0, draw = 0;
		for (int i = 0; i < num; i++) {
			Board board;
			Othello game(board, user, computer);
			Disc winner = game.run();
			if (winner == BLACK)
				black++;
			else if (winner == WHITE)
				white++;
			else
				draw++;
		}
		cout << "Black: " << black << endl;
		cout << "White: " << white << endl;
		cout << "Draw: " << draw << endl;
	}
	return 0;
}