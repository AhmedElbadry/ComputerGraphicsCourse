#pragma once
#include "global.h"

using namespace std;

class Button {

public:
	char name[20];
	double x;
	double y;
	Color color;
	
	double width;
	Button(double xx, double yy, double ww, Color c);
	void draw();
	void buttonClicked();

};