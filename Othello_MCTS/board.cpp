#include "board.h"
#include "string"
#include <cstring>

Board::Board() {
	memset(&board, EMPTY, 64 * sizeof(Disc));
}

Board::Board(const Board &obj) {
	memcpy(&board, obj.board, 64 * sizeof(Disc));
}

Disc Board::operator() (int x, int y) const {
	return board[x][y];
}

void Board::printBoard() {
	cout << "    1   2   3   4   5   6   7   8  " << endl;
	cout << "   --- --- --- --- --- --- --- --- " << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << char('A' + i) << " |";
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == EMPTY)
				cout << " * |";
			else if (board[i][j] == BLACK)
				cout << " X |";
			else
				cout << " O |";
		}
		cout << endl;
		cout << "   --- --- --- --- --- --- --- --- " << endl;
	}
}

bool Board::onBoard(int x, int y) {
	return x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE;
}


bool Board::onCorner(int x, int y) {
	return (x == 0 && y == 0) || (x == 7 && y == 7) || (x == 0 && y == 7) || (x == 7 && y == 0);
}

bool Board::onXSquare(int x, int y) {
	return (x == 1 && y == 1) || (x == 1 && y == 6) || (x == 6 && y == 1) || (x == 6 && y == 6);
}

bool Board::onCSquare(int x, int y) {
	return (x == 0 && y == 1) || (x == 0 && y == 6) || (x == 1 && y == 0) || (x == 1 && y == 7) ||
		   (x == 6 && y == 0) || (x == 6 && y == 7) || (x == 7 && y == 1) || (x == 7 && y == 6);
}

void BoardLogic::setTile(Disc side, int x, int y) {
	board.board[x][y] = side;
}

bool BoardLogic::isThereValidMove(Disc side) {
	int direction[3] = { -1, 0, 1 };
	Disc opponent = getOpponent(side);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board(i, j) == EMPTY) {
				board.board[i][j] = side;
				for (int s = 0; s < 3; s++) {
					for (int k = 0; k < 3; k++) {
						if (!direction[s] && !direction[k])
							continue;
						int x = i, y = j;
						x += direction[s];
						y += direction[k];

						if (Board::onBoard(x, y) && board(x, y) == opponent) {
							while (board(x, y) == opponent) {
								x += direction[s];
								y += direction[k];
								if (!Board::onBoard(x, y))
									break;
							}
							if (!Board::onBoard(x, y))
								continue;
							if (board(x, y) == side) {
								board.board[i][j] = EMPTY;
								return true;
							}
						}
					}
				}
				board.board[i][j] = EMPTY;
			}
		}
	}
	return false;
}

Disc BoardLogic::run() {
	board.printBoard();
	while (playTurn());
	pair<int, int> score = getScore(board);
	cout << "BLACK: " << score.first << " WHITE: " << score.second << endl;
	if (score.first > score.second) {
		cout << "Winner is BLACK" << endl;
		return BLACK;
	}
	else if (score.second > score.first) {
		cout << "Winner is WHITE" << endl;
		return WHITE;
	}
	else {
		cout << "DRAW" << endl;
		return EMPTY;
	}
}

bool isValidMove(Board &aBoard, Disc side, pair<int, int> pos) {
	int direction[3] = { -1, 0, 1 };
	Disc opponent = side == WHITE ? BLACK : WHITE;
	aBoard.board[pos.first][pos.second] = side;
	bool ret = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!direction[i] && !direction[j])
				continue;
			int x = pos.first, y = pos.second;
			x += direction[i];
			y += direction[j];

			if (Board::onBoard(x, y) && aBoard(x, y) == opponent) {
				while (aBoard(x, y) == opponent) {
					x += direction[i];
					y += direction[j];
					if (!Board::onBoard(x, y))
						break;
				}
				if (!Board::onBoard(x, y))
					continue;
				if (aBoard(x, y) == side) {
					ret = true;
					while (x != pos.first || y != pos.second) {
						x -= direction[i];
						y -= direction[j];
						aBoard.board[x][y] = side;
					}
				}
			}
		}
	}
	if (!ret)
		aBoard.board[pos.first][pos.second] = EMPTY;
	return ret;
}
vector<Board> getAllPossibleMoves(Board &aBoard, Disc side) {
	vector<Board> ret;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (aBoard(i, j) == EMPTY) {
				Board temp = aBoard;
				if (isValidMove(temp, side, { i, j }))
					ret.push_back(temp);
			}
		}
	}
	return ret;
}

Disc getOpponent(Disc side) {
	return side == WHITE ? BLACK : WHITE;
}

pair<int, int> getScore(const Board &board) {
	int black = 0, white = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board(i, j) == WHITE)
				white++;
			else if (board(i, j) == BLACK)
				black++;
		}
	}
	return { black, white };
}

Disc whoIsWinner(const Board &board) {
	pair<int, int> score = getScore(board);
	if (score.first > score.second)
		return BLACK;
	else if (score.second > score.first)
		return WHITE;
	else
		return EMPTY;
}