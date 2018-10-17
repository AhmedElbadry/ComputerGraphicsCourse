#include "BST.h"
#include "Node.h"
#include<algorithm>
#include<stdlib.h>
#include<iostream>
#include <math.h>

using namespace std;

void BST::update() {

	levels = getLevel__private(root);
	levelHeight = WINDOW_HEIGHT / levels;
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

	currNode->x = WINDOW_WIDTH / 2 + (WINDOW_WIDTH / (pow(2, level)))*col;
					//+ ((int)(col != 0))*((col > 0) ? -1 : 1)*(WINDOW_WIDTH / (2 * level))/2;


	currNode->y = WINDOW_HEIGHT - (level*levelHeight - levelHeight / 2);



	cout << "\n\nnode date = " << ((int)(col != 0)) << "\n\n";

	//mesure the positions
	

	updatePositions__private(currNode->left, level + 1, col - 1);
	updatePositions__private(currNode->right, level + 1, col + 1);
}