#include"button.h"
#include<iostream>
#include<glut.h>
#include<math.h>
#include<algorithm>
#include"global.h"
Button::Button(double xx, double yy, double ww, Color c) {
	x = xx;
	y = yy;
	width = ww;
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
}

void Button::draw() {

	glColor3f(color.r, color.g, color.b);
	double halfWidth = width / 2;
	glBegin(GL_POLYGON);
		glVertex2f(x - halfWidth, y + halfWidth);
		glVertex2f(x + halfWidth, y + halfWidth);
		glVertex2f(x + halfWidth, y - halfWidth);
		glVertex2f(x - halfWidth, y - halfWidth);
	glEnd();


}