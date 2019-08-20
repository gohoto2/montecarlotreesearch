#pragma once
#include <vector>
#include <utility>
#include <iostream>

#define BOARD_SIZE 8

using namespace std;

enum Disc {
	BLACK = -1,
	EMPTY,
	WHITE
};
class Board {
	private:
		Disc board[BOARD_SIZE][BOARD_SIZE];
	public:
		Board();
		Board(const Board &obj);
		~Board() {};
		Disc operator()(int x, int y) const;
		static bool onBoard(int x, int y);
		static bool onCorner(int x, int y);
		static bool onXSquare(int x, int y);
		static bool onCSquare(int x, int y);
		void printBoard();
		friend class BoardLogic;
		friend bool isValidMove(Board &aBoard, Disc side, pair<int, int> pos);
		friend vector<Board> getAllPossibleMoves(Board &board, Disc side);
};

class BoardLogic {
	protected:
		Board &board;
		void setTile(Disc side, int x, int y);
		virtual bool playTurn() = 0;
	public:
		BoardLogic(Board &board) : board(board) {};
		BoardLogic(BoardLogic &obj) : board(obj.board) {};
		bool isThereValidMove(Disc side);
		Disc run();
};

Disc getOpponent(Disc side);
pair<int, int> getScore(const Board &board);
Disc whoIsWinner(const Board &board);