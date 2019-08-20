#include "mcts.h"
#include <stdlib.h>
#include <ctime>  
#include <chrono>
#include <iostream>
#include <string>

Node *MCTS::selection(Node *root) {
	while (root->children.size()) {
		root = findBestNodeWithUCT(root);
	}
	return root;
}

Node *MCTS::expansion(Node *node) {
	node->children = getAllPossibleNodes(node);
	if (node->children.empty())
		return node;
	srand(time(0));
	int randomNumber = rand() % node->children.size();
	return node->children[randomNumber];
}

Disc MCTS::randomPlayout(Node *node) {
	vector<Board> possibleMoves;
	Board temp = node->board;
	Disc currentSide = node->side;
	while (true) {
		possibleMoves = getAllPossibleMoves(temp, currentSide);
		if (possibleMoves.empty()) {
			// check if the opponent also has no valid moves
			possibleMoves = getAllPossibleMoves(temp, getOpponent(currentSide));
			// if empty
			if (possibleMoves.empty())
				return whoIsWinner(temp);
		}
		currentSide = getOpponent(currentSide);
		srand(time(0));
		int randomNumber = rand() % possibleMoves.size();
		temp = possibleMoves[randomNumber];
	}
}

Disc MCTS::heuristicsPlayout(Node *node) {
	vector<Board> possibleMoves;
	Board temp = node->board;
	Disc currentSide = node->side;
	while (true) {
		possibleMoves = getAllPossibleMoves(temp, currentSide);
		if (possibleMoves.empty()) {
			// check if the opponent also has no valid moves
			currentSide = getOpponent(currentSide);
			possibleMoves = getAllPossibleMoves(temp, currentSide);
			// if empty
			if (possibleMoves.empty())
				return whoIsWinner(temp);
		}
		// Evaluate each board
		vector<pair<int, int>> vec;
		int maxScore = numeric_limits<int>::min();;
		for (int i = 0; i < possibleMoves.size(); i++) {
			int score = getStaticEvaluation(possibleMoves[i], currentSide);
			if (score >= maxScore) {
				maxScore = score;
				vec.push_back({ score, i });
			}
		}
		if (vec.size() == 1) {
			temp = possibleMoves[vec[0].second];
			continue;
		}
		int start = vec.size() - 1;
		while (start > 0 && vec[start - 1].first == vec[start].first)
			start--;
		int size = vec.size() - start;

		srand(time(0));
		int randomNumber = start + rand() % size;
		temp = possibleMoves[vec[randomNumber].second];
		currentSide = getOpponent(currentSide);
	}
}

/*
 * A winner gets 1.0 point. Both sides get 0.5 points for draw.
 */

void MCTS::backpropagation(Node *node, Disc winner) {
	Disc opponent = getOpponent(winner);
	while (node != nullptr) {
		node->n++;
		if (node->side == EMPTY)
			node->w += 0.5;
		else if (node->side != winner)
			node->w += 1.0;
		node = node->parent;
	}
}

/*
 * Return the most visited child
 */

Node *MCTS::findNextMove(Node *root) {
	if (root->children.empty())
		return root;
	int max_n = 0;
	Node *ret = root->children[0];
	for (Node *node : root->children) {
		if (node->n > max_n) {
			max_n = node->n;
			ret = node;
		}
	}
	return ret;
}

Node *MCTS::runMCTS(Node *root, bool heuristic) {
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	int iteration = 0;
	while (iteration < ITERATION_LIMIT && chrono::duration_cast<chrono::seconds>(end - start).count() < 5) {
		// Start Monte Carlo Tree Search
		// 1. Selection
		Node *node = selection(root);
		// 2. Expansion
		Node *expandedNode = expansion(node);
		// 3. Simulation
		Disc winner = heuristic ? heuristicsPlayout(expandedNode) : randomPlayout(expandedNode);
		// 4. Backpropagation
		backpropagation(expandedNode, winner);
		end = chrono::steady_clock::now();
		iteration++;
	}
	return findNextMove(root);
}

int MCTS::getStaticEvaluation(const Board &board, Disc side) {
	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board(i, j) == side) {
				if (Board::onCSquare(i, j))
					score--;
				else if (Board::onCorner(i, j))
					score += 5;
				else if (Board::onXSquare(i, j))
					score -= 2;
				else
					score++;
			}
		}
	}
	return score;
}