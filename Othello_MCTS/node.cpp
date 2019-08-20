#include "node.h"

double calculateUCT(int t, int n, double w) {
	if (n == 0)
		return numeric_limits<double>::max();
	return (w / n) + 1.41 * sqrt(log(t) / n);
}

Node *findBestNodeWithUCT(Node *node) {
	double max = calculateUCT(node->n, node->children[0]->n, node->children[0]->w);
	Node *ret = node->children[0];
	for (int i = 1; i < node->children.size(); i++) {
		double temp = calculateUCT(node->n, node->children[i]->n, node->children[i]->w);
		if (temp > max) {
			max = temp;
			ret = node->children[i];
		}
	}
	return ret;
}

vector<Node*> getAllPossibleNodes(Node *node) {
	vector<Node*> ret;
	vector<Board> possibleMoves = getAllPossibleMoves(node->board, node->side);
	if (possibleMoves.empty())
		return ret;
	for (Board b : possibleMoves) {
		Node *newNode = new Node(node, b, getOpponent(node->side));
		ret.push_back(newNode);
	}
	return ret;
}

void deleteNodes(Node *root) {
	if (!root->children.empty()) {
		for (Node *child : root->children)
			deleteNodes(child);
	}
	delete root;
}