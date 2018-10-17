#pragma once
#include<stdlib.h>

struct Node {
	int data;
	Node* left;
	Node* right;
	int level;
	int col;

	Node();
	Node(int);

	void connectWithChildren();
};
