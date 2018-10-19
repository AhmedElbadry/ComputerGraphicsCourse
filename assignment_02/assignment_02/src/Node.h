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


	double currX = 0;
	double currY = 0;
	

	bool isInPosition = false;

	Node();
	Node(int);

	void connectWithChildren();

	void drawText();

	void draw();

	bool goToPos();
};
