#pragma once

#include "board.h"
#include "controller.h"

class Othello : public BoardLogic {
	public:
		Controller &black;
		Controller &white;
		Othello(Board &board, Controller &player1, Controller &player2);
		bool playTurn();
};