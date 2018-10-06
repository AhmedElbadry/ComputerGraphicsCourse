
#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <glut.h>
#include <math.h>
#define PI 3.14159265
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

int NumOfSides = 4;

using namespace std;

void handleKeypress(unsigned char key, int x, int y);
void drawPolygon(int numOfEdges);
void drawScene();
void resize(int width, int height);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //Set the window size

	//Create the window
	glutCreateWindow("Assignment 1");

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(mouse);
	glutReshapeFunc(resize);

	

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
}


//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	switch (key) {
	case 27: //Escape key
		exit(0); //Exit the program
	}
}



void drawPolygon(int numOfSides) {



	glBegin(GL_POLYGON);

	for (int i = 0; i < numOfSides; i++) {
		float currX = cos( (2 * PI*(i / (numOfSides*1.0) ))   + (2 * PI*(1 / (numOfSides*1.0)))/2 );
		float currY = sin((2 * PI*(i / (numOfSides * 1.0))) + (2 * PI*(1 / (numOfSides*1.0)))/2 );

		/*
		cout << "x" << i << " = " << currX << endl;
		cout << "y" << i << " = " << currY << endl;
		*/

		glVertex2f(currX, currY);

	}

	glEnd();
}



void drawScene() {

	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawPolygon(NumOfSides);
	/*
	glBegin(GL_POLYGON);

	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, 0.0f);

	glEnd();*/

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		NumOfSides++;
		cout << NumOfSides << endl;
	}
}


void resize(int width, int height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // don't resize the window 
}

