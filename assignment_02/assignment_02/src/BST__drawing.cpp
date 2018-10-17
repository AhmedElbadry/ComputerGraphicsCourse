#include "BST.h"
#include "Node.h"
#include<algorithm>
#include<stdlib.h>
#include<iostream>

using namespace std;

void BST::update() {

	levels = getLevel__private(root);
	updatePositions__private(root, 1, 0);

}

int BST::getLevel__private(Node* currNode) {
	if (currNode == NULL)
		return 0;
	return max(getLevel__private(currNode->left) + 1, getLevel__private(currNode->right) + 1);
}

void BST::updatePositions__private(Node* currNode, int level, int col) {
	if (!currNode) return;

	currNode->level = level;
	currNode->col = col;

	//cout << "\n\nnode date = " << currNode->data << "\n\n";

	updatePositions__private(currNode->left, level + 1, col - 1);
	updatePositions__private(currNode->right, level + 1, col + 1);
}