#pragma once

#include "board.h"

class Controller {
	public:
		enum MoveType {
			MOVE,
			QUIT,
			INVALID
		};
		Disc side;
		Controller() {};
		Controller(Disc side) : side(side) {};
		void setSide(Disc side);
		virtual MoveType getNewMove(Board &board) = 0;
};

class UserController : public Controller {
	public:
		UserController() {};
		UserController(Disc side) : Controller(side) {};
		MoveType getNewMove(Board &board);
		pair<int, int> inputValidator(string str);
};

class ComputerController : public Controller {
	public:
		bool heuristic;
		ComputerController() { this->heuristic = false; };
		ComputerController(Disc side) : Controller(side) { this->heuristic = false; };
		ComputerController(Disc side, bool heuristic) : Controller(side), heuristic(heuristic) {};
		void useHeuristic();
		MoveType getNewMove(Board &board);
};