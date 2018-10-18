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



	Button(string nn, double xx, double yy, double ww, double hh, Color c);
	void draw();
	void buttonClicked();
	void checkForMouseClick(int mouseX, int mouseY);

};