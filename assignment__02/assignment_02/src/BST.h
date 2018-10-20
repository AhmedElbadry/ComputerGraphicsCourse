#pragma once
#include "Node.h"
class BST {
public:
	BST();
	Node* root;
	int insert(int x);
	void print();
	void deleteNode(int x);
	Node* findNode(int x);
	Node* findMax();
	void update();
	void draw();
private:
	void print__private(Node* node);
	Node* findMax__private(Node* node);
	Node* deleteNode__private(Node* node, int x);
	int getLevel__private(Node* currNode);
	void updatePositions__private(Node* currNode, int level, int col);
	void draw__private(Node* currNode);
	Node* FindMax(Node* r);
};


