#pragma once
#include<stdlib.h>
struct Node {
	int data;
	Node* left;
	Node* right;
	int level;
	int col;
	
	float x;
	float y;
	float currX;
	float currY;
	

	bool isInPosition;

	Node();
	Node(int);

	void connectWithChildren();
};
