#include "controller.h"
#include "node.h"
#include "mcts.h"
#include <string>

void Controller::setSide(Disc side) {
	this->side = side;
}

pair<int, int> UserController::inputValidator(string str) {
	pair<int, int> ret = { -1, -1 };
	if (str.length() != 2) {
		cout << "Invalid input" << endl;
		return ret;
	}

	if (str[0] >= 'A' && str[0] <= 'Z')
		ret.first = str[0] - 'A';
	else {
		cout << "Invalid input" << endl;
		return ret;
	}
	if (str[1] >= '1' && str[1] <= '9')
		ret.second = str[1] - '1';
	else
		cout << "Invalid input" << endl;
	return ret;
}

Controller::MoveType UserController::getNewMove(Board &board) {
	pair<int, int> pos;
	string str;
	cout << "If you want to quit, type q" << endl;
	cout << "Your turn: ";
	cin >> str;
	if (str.length() == 1 && str[0] == 'q') 
		return QUIT;
	pos = inputValidator(str);
	if (Board::onBoard(pos.first, pos.second) && board(pos.first, pos.second) == EMPTY && isValidMove(board, this->side, pos))
		return MOVE;
	return INVALID;
}

Controller::MoveType ComputerController::getNewMove(Board &board) {
	Node *root = new Node(nullptr, board, this->side);
	MCTS mcts(7, 1000);
	Node *node = mcts.runMCTS(root, heuristic);
	if (node != root)
		board = node->board;
	deleteNodes(root);
	return MOVE;
}

void ComputerController::useHeuristic() {
	heuristic = true;
}