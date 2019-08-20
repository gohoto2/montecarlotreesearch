#pragma once

#include "node.h"

class MCTS {
private:
	size_t DEPTH_LIMIT;
	size_t ITERATION_LIMIT;
public:
	MCTS(size_t dlimit, size_t ilimit) : DEPTH_LIMIT(dlimit), ITERATION_LIMIT(ilimit) {};
	// Selection
	Node *selection(Node *root);
	// Expansion
	Node *expansion(Node *node);
	// Simulation
	Disc randomPlayout(Node *node);
	Disc heuristicsPlayout(Node *node);
	// backpropagation
	void backpropagation(Node *node, Disc winner);
	// Find a next move
	Node *findNextMove(Node *node);
	Node *runMCTS(Node *root, bool heuristic);
	int getStaticEvaluation(const Board &board, Disc side);
};
