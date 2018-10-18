#include<iostream>
#include<glut.h>
#include<math.h>
#include<algorithm>
#include "BST.h"
#include "funcDeclarations.h"
using namespace std;


#define PI acos(-1)
const double WINDOW_WIDTH = 1100.0;
const double WINDOW_HEIGHT = 700.0;
const double MAX_NODE_RADIUS = 100.0;
const double MIN_NODE_RADIOUS = 40;


int levels;
double levelHeight;
double nodeRadius;




double CR = 200.0f;

BST tree;



void initGL(void)
{
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0); //specifies clear values for the color buffers(R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION); // sets the current matrix mode
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT); //2D orthographic projection matrix(left, right, bottom, top)

}


void BST::draw() {
	draw__private(root);
}
void BST::draw__private(Node* currNode) {
	if (!currNode) return;

	drawCircle(currNode->x, currNode->y, nodeRadius);

	currNode->draw();

	draw__private(currNode->left);
	draw__private(currNode->right);
}

void Node::draw() {


	connectWithChildren();
	drawText();
}
void Node::drawText() {

	char tmp[10];
	int theData = data;

	int index = 0;
	while (theData) {
		tmp[index] = '0' + theData % 10;
		theData /= 10;
		index++ ;
	}
	char str[10];
	for (int i = 0; i < index; i++) 
		str[i] = tmp[index - i - 1];
	
	::drawText(x, y, str);
}
void BST::update() {

	levels = getLevel__private(root);
	levelHeight = WINDOW_HEIGHT / levels;
	updatePositions__private(root, 1, 1);

	nodeRadius = min(
		min(((WINDOW_WIDTH / pow(2, levels)*1.0) / 2)*0.8, ((WINDOW_HEIGHT / levels) / 2)*0.8)
		, MAX_NODE_RADIUS);
	nodeRadius = max(nodeRadius, MIN_NODE_RADIOUS);
}

int BST::getLevel__private(Node* currNode) {
	if (currNode == NULL)
		return 0;
	return max(getLevel__private(currNode->left) + 1, getLevel__private(currNode->right) + 1);
}

void BST::updatePositions__private(Node* currNode, int level, int col) {
	if (!currNode) return;

	currNode->level = level;
	currNode->col = col;

	int absCol = col - pow(2, level - 1) + 1;

	double ww = (WINDOW_WIDTH / pow(2, level - 1));

	currNode->x = ww * (absCol - 1) + ww / 2;


	currNode->y = WINDOW_HEIGHT - (level*levelHeight - levelHeight / 2);

	

	cout << "\n\nnode date = " << absCol << "\n\n";

	//mesure the positions
	updatePositions__private(currNode->left, level + 1, col << 1);
	updatePositions__private(currNode->right, level + 1, (col << 1)|1);
}

void Node::connectWithChildren() {
	if (left) {
		glBegin(GL_LINES);
			glVertex2f(x, y);
			glVertex2f(left->x, left->y);
		glEnd();
	}
	if (right) {
		glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(right->x, right->y);
		glEnd();
	}
}


void drawText(double x, double y, const char *string) {
	glColor3f(0.0, 0.0, 0.0);
	
	cout << "text = " << string << endl;
	int j = strlen(string);

	double textWidth = 0;

	for (int i = 0; i < j; i++) {
		textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, string[i]);
	}

	glRasterPos2f(x - textWidth/2, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		
	}
}
void drawCircle(double x, double y, double r) {
	glColor3f(1.0, 0.0, 0.0);
	int iterations = 360;
	glBegin(GL_POLYGON);
	for (int i = 0; i < iterations; i++) {
		double currX = r * cos(2 * PI*(i / (iterations * 1.0)));
		double currY = r * sin(2 * PI*(i / (iterations * 1.0)));
		glVertex2f(x + currX, y + currY);
	}
	glEnd();



}

void mainLoop() {

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	//drawCircle(200.0f, 200.0f, CR);
	//char str[] = "AAHHNA";
	//displayText(500.0f, 500.0f, str);

	tree.draw();
	glFlush();
}


void handleResize(int width, int height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // don't resize the window 
}

void main(int argc, char** argv)
{

	tree.insert(20);
	tree.insert(10);
	tree.insert(15);
	tree.insert(7);
	tree.insert(30);
	tree.insert(40);
	tree.insert(25);
	tree.insert(23);
	tree.insert(22);
	tree.insert(55);
	tree.print();
	//tree.update();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Binary Search Tree Visualization");
	initGL();
	glutReshapeFunc(handleResize);
	glutDisplayFunc(mainLoop);
	glutIdleFunc(mainLoop);
	glutMainLoop();


	

}
