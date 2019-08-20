#pragma once

#include "board.h"
#include <limits>
#include <cmath>

typedef struct Node {
	Node *parent;
	vector<Node*> children;
	Board board;
	Disc side;
	int n;
	double w;
	Node(Node *node, Board &aBoard, Disc aSide) : parent(node), board(aBoard), side(aSide), n(0), w(0) {};
} Node;

double calculateUCT(int t, int n, double w);
Node *findBestNodeWithUCT(Node *node);
void deleteNodes(Node *root);
vector<Node*> getAllPossibleNodes(Node *node);