#include"button.h"
#include<iostream>
#include<glut.h>
#include<math.h>
#include<algorithm>
#include"global.h"
#include<string>
Button::Button(string nn, double xx, double yy, double ww, double hh, Color c, bool isV) {
	name = nn;
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	opened = false;
	isVisible = isV;
}
Button::Button() {

}
void Button::draw() {

	glColor3f(color.r, color.g, color.b);
	double halfWidth = width / 2;
	double hafHeight = height / 2;

	glBegin(GL_POLYGON);
		glVertex2f(x - halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y - hafHeight);
		glVertex2f(x - halfWidth, y - hafHeight);
	glEnd();

	drawText(x, y, txtColor, name);


}