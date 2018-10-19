#pragma once
#include "global.h"
#include <string>
using namespace std;

class Button {

public:
	bool opened;
	string name;
	double x;
	double y;
	Color color;
	double width;
	double height;
	Color txtColor = Color(1.0, 1.0, 0.0);
	bool isVisible = false;

	Button();
	Button(string nn, double xx, double yy, double ww, double hh, Color c, bool isV);
	void draw();
	void buttonClicked();
	bool checkForMouseClick(int mouseX, int mouseY);

};