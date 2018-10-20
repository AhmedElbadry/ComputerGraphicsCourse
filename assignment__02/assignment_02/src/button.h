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
	Color textColor;
	bool isVisible = false;
	double iconLineWidth = 4;
	Button();
	Button(string nn, double xx, double yy, double ww, double hh, Color c, Color tt, bool isV);
	void draw();
	void buttonClicked();
	bool checkForMouseClick(int mouseX, int mouseY);

};