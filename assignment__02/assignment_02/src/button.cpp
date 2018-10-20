#include"button.h"
#include<iostream>
#include<glut.h>
#include<math.h>
#include<algorithm>
#include"global.h"
#include<string>
#include<glut.h>
Button::Button(string nn, double xx, double yy, double ww, double hh, Color c, Color tt, bool isV) {
	name = nn;
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;

	textColor.r = tt.r;
	textColor.g = tt.g;
	textColor.b = tt.b;

	opened = false;
	isVisible = isV;


}
Button::Button() {

}
void Button::draw() {

	glColor3f(color.r, color.g, color.b);
	double halfWidth = width / 2;
	double hafHeight = height / 2;
	double iconPercentage = 0.4;
	double iconHalfWidth = iconPercentage * halfWidth;
	double iconHalfHeight = iconPercentage * hafHeight;
	glBegin(GL_POLYGON);
		glVertex2f(x - halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y - hafHeight);
		glVertex2f(x - halfWidth, y - hafHeight);
	glEnd();

	glColor3f(textColor.r, textColor.g, textColor.b);
	glLineWidth(iconLineWidth);
	if (name == "ADD") {
		
		glBegin(GL_LINES);
			glVertex2f(x, y + iconHalfHeight);
			glVertex2f(x , y - iconHalfHeight);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(x - iconHalfWidth, y);
			glVertex2f(x + iconHalfWidth, y);
		glEnd();

	}
	else if (name == "DELETE") {
		glBegin(GL_LINES);
			glVertex2f(x - iconHalfWidth, y);
			glVertex2f(x + iconHalfWidth, y);
		glEnd();
	}
	else if (name == "CLOSE") {
		glBegin(GL_LINES);
			glVertex2f(x - iconHalfWidth, y + iconHalfHeight);
			glVertex2f(x + iconHalfWidth, y - iconHalfHeight);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(x - iconHalfWidth, y - iconHalfHeight);
			glVertex2f(x + iconHalfWidth, y + iconHalfHeight);
		glEnd();
	}
	else {
		drawText(x, y, textColor, name, GLUT_BITMAP_HELVETICA_12);
	}
	


}