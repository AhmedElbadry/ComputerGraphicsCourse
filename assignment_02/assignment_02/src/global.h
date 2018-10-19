#pragma once
#include<string>
using namespace std;


struct Color{
	double r, g, b;
	Color();
	Color(double rr, double gg, double bb);
};

struct State {
	bool addModalOpenned = false;
	bool deleteModalOpenned = false;
	bool addNodeTransition = false;
};


void drawCircle(double x, double y, double r);

void drawText(double x, double y, Color cc, string str, void *font);

void mouse(int button, int state, int x, int y);
void closeAllModals();

void handleKeypress(unsigned char key, int x, int y);