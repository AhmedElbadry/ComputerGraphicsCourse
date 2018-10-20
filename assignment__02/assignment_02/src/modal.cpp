#include"modal.h"
#include"global.h"
#include<string>
#include<glut.h>
#include"button.h"
using namespace std;
Modal::Modal(string nn, double xx, double yy, double ww, double hh, Color cc) {
	name = nn;
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	color = cc;
	inputText = "";
}

void Modal::draw() {
	glColor3f(color.r, color.g, color.b);
	double halfWidth = width / 2;
	double hafHeight = height / 2;

	glBegin(GL_POLYGON);
		glVertex2f(x - halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y + hafHeight);
		glVertex2f(x + halfWidth, y - hafHeight);
		glVertex2f(x - halfWidth, y - hafHeight);
	glEnd();
	showInputText();
}

void Modal::updateInputText(string inputText) {

}