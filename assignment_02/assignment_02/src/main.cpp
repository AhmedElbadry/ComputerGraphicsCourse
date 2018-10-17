#include<iostream>
#include<glut.h>
#include<math.h>
#include "BST.h"
#define PI acos(-1)

using namespace std;

const float WINDOW_WIDTH = 1100.0;
const float WINDOW_HEIGHT = 700.0;

float CR = 200.0f;


void init(void)
{
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0); //specifies clear values for the color buffers(R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION); // sets the current matrix mode
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT); //2D orthographic projection matrix(left, right, bottom, top)
}
void displayText(float x, float y, const char *string) {
	int j = strlen(string);

	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		//cout << glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, string[i]) << endl;
	}
}
void drawCircle(float x, float y, float r) {

	int iterations = 360;
	glBegin(GL_POLYGON);
	for (int i = 0; i < iterations; i++) {
		float currX = r * cos(2 * PI*(i / (iterations * 1.0)));
		float currY = r * sin(2 * PI*(i / (iterations * 1.0)));
		glVertex2f(x + currX, y + currY);
	}
	glEnd();



}

void mainLoop() {

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	drawCircle(200.0f, 200.0f, CR);
	char str[] = "AAHHNA";
	displayText(500.0f, 500.0f, str);
	glFlush();
}


void handleResize(int width, int height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // don't resize the window 
}

void main(int argc, char** argv)
{
	BST tree;

	tree.insert(20);
	tree.insert(10);
	tree.insert(15);
	tree.insert(7);
	tree.insert(30);
	tree.insert(40);
	tree.insert(25);
	tree.insert(23);
	tree.print();
	tree.deleteNode(10);
	tree.print();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Binary Search Tree Visualization");
	init();
	glutReshapeFunc(handleResize);
	glutDisplayFunc(mainLoop);
	glutIdleFunc(mainLoop);
	glutMainLoop();


	

}