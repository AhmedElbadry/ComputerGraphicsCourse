#pragma once
#include<stdlib.h>
struct Node {
	int data;
	Node* left;
	Node* right;
	int level;
	int col;
	
	double x;
	double y;
	double currX;
	double currY;
	

	bool isInPosition;

	Node();
	Node(int);

	void connectWithChildren();

	void drawText();

	void draw();
};
