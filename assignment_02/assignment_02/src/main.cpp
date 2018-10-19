#include<iostream>
#include<glut.h>
#include<math.h>
#include<algorithm>
#include "BST.h"
#include "global.h"
#include "button.h"
#include "modal.h"
#include<string>

using namespace std;

#define PI acos(-1)
const double EP = 0.1;
const double WINDOW_WIDTH = 1100.0;
const double WINDOW_HEIGHT = 700.0;
const double MAX_NODE_RADIUS = 80.0;
const double MIN_NODE_RADIOUS = 40;
const double BUTTON_WIDTH = 50;
const double BUTTON_HEIGHT = 50;
const double BUTTON_TOP_MARGIN = 80.0;
const double MODAL_WIDTH = 500;
const double MODAL_HEIGHT = 300;
const double CLOSE_BUTTON_MARGIN = 10;
const double CLOSE_BUTTON_WIDTH = 40;
const double CLOSE_BUTTON_HEIGHT = 40;
const double MODAL_SUBMIT_BUTTON_WIDTH = 120;
const double MODAL_SUBMIT_BUTTON_HEIGHT = 50;
double modalX = WINDOW_WIDTH / 2;
double modalY = WINDOW_HEIGHT / 2;
double nodeSpeed = .8;


string inputHolder;
Color mainBgColor(165 / 255.0, 145 / 255.0, 190 / 255.0);
Color buttonColor(0.0, 0.0, 0.0);
Color buttonTextColor(1.0, 1.0, 1.0);
Color moadalColor(224 / 255.0, 224 / 255.0, 113 / 255.0);
Color modalTexColor(0.0, 0.0, 0.0);
Color modalSubmitButtonColor(0.0, 0.0, 0.0);
Color modalSubmitButtonTextColor(1.0, 1.0, 1.0);

Color nodeBGClolor(1.0, 1.0, 1.0);
Color nodeSrokeClolor(0.0, 0.0, 0.0);
Color nodeTextColor(0.0, 0.0, 0.0);
Color closeButtonColor(0.0, 0.0, 0.0);

Color textColor(1.0, 1.0, 1.0);

int levels;
double levelHeight;
double nodeRadius;
double nodeCurrentRadius = 40;
double nodeRadiusStep = .2;

State state;



Button addButton(
	"ADD",
	BUTTON_WIDTH/2,
	WINDOW_HEIGHT - BUTTON_TOP_MARGIN,
	BUTTON_WIDTH,
	BUTTON_HEIGHT,
	buttonColor,
	buttonTextColor,
	true
);
Button deleteButton(
	"DELETE",
	BUTTON_WIDTH / 2,
	WINDOW_HEIGHT - BUTTON_TOP_MARGIN - BUTTON_HEIGHT - 10,
	BUTTON_WIDTH,
	BUTTON_HEIGHT,
	buttonColor,
	buttonTextColor,
	true
);

Button closeButton(
	"CLOSE",
	modalX + MODAL_WIDTH / 2 - CLOSE_BUTTON_WIDTH / 2 - CLOSE_BUTTON_MARGIN,
	modalY + MODAL_HEIGHT / 2 - CLOSE_BUTTON_HEIGHT / 2 - CLOSE_BUTTON_MARGIN,
	CLOSE_BUTTON_WIDTH,
	CLOSE_BUTTON_HEIGHT,
	closeButtonColor,
	buttonTextColor,
	false
);



Modal addModal(
	"ADD",
	modalX,
	modalY,
	MODAL_WIDTH,
	MODAL_HEIGHT,
	moadalColor
);
Button addModal__submitButton(
	"ADD NODE",
	modalX,
	modalY - 50,
	MODAL_SUBMIT_BUTTON_WIDTH,
	MODAL_SUBMIT_BUTTON_HEIGHT,
	modalSubmitButtonColor,
	modalSubmitButtonTextColor,
	false
);

Modal deleteModal(
	"DELETE",
	modalX,
	modalY,
	MODAL_WIDTH,
	MODAL_HEIGHT,
	moadalColor
);
Button deleteModal__submitButton(
	"DELETE NODE",
	modalX,
	modalY - 50,
	MODAL_SUBMIT_BUTTON_WIDTH,
	MODAL_SUBMIT_BUTTON_HEIGHT,
	modalSubmitButtonColor,
	modalSubmitButtonTextColor,
	false
);


BST tree;



void initGL(void)
{
	glLoadIdentity();
	glClearColor(mainBgColor.r, mainBgColor.g, mainBgColor.b, 0.0); //specifies clear values for the color buffers(R, G, B, Alpha)
	glMatrixMode(GL_PROJECTION); // sets the current matrix mode
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT); //2D orthographic projection matrix(left, right, bottom, top)

}


void BST::draw() {
	draw__private(root);
}
void BST::draw__private(Node* currNode) {
	if (!currNode) return;


	currNode->draw();

	draw__private(currNode->left);
	draw__private(currNode->right);
}

void Node::draw() {
	
	

	isInPosition = goToPos();

	
	drawCircle(0, 0, 1);
	connectWithChildren();
	drawCircle(currX, currY, nodeCurrentRadius);
	drawText();
}

void Node::drawText() {

	string str = to_string(data);
	::drawText(currX, currY, nodeTextColor, str, GLUT_BITMAP_HELVETICA_18);
}

bool Node::goToPos() {
	
	double y1 = currY;
	double x1 = currX;
	double dy = (y - currY);
	double dx = (x - currX);
	double slope = dy / dx;

	if (abs(dy) > nodeSpeed || abs(dx) > nodeSpeed) {
		if (abs(dy) > abs(dx)) {

			if (y > currY)
				currY += nodeSpeed;
			else
				currY -= nodeSpeed;

			if (slope == 0) {
				currX += nodeSpeed;
			}
			else
				currX = (currY + slope * x1 - y1) / slope;

			if (abs(slope) < EP) {
				if (x > currX)
					currX += nodeSpeed;
				else
					currX -= nodeSpeed;
			}
			else {
				currX = (currY + slope * x1 - y1) / slope;
			}

		}
		else {
			if (x > currX)
				currX += nodeSpeed;
			else
				currX -= nodeSpeed;

			if (abs(slope) < EP) {
				if(y > currY)
					currY += nodeSpeed;
				else
					currY -= nodeSpeed;
			}
			else {
				currY = (slope* currX - slope * x1 + y1);
			}
				
			
		}
		return false;
	}
	else {

		//currX = x;
		//currY = y;

		

		return true;
	}
		
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
	
	cout << "update\n";
	cout << "node date = " << currNode->data << endl;
	cout << "currNode->x" << currNode->x << endl;
	cout << "currNode->y" << currNode->y << endl;
	cout << "currNode->currX" << currNode->currX << endl;
	cout << "currNode->currY" << currNode->currY << endl;

	int absCol = col - pow(2, level - 1) + 1;

	double ww = (WINDOW_WIDTH / pow(2, level - 1));

	currNode->x = ww * (absCol - 1) + ww / 2;


	currNode->y = WINDOW_HEIGHT - (level*levelHeight - levelHeight / 2);
	
	cout << "after\n";
	cout << "currNode->x" << currNode->x << endl;
	cout << "currNode->y" << currNode->y << endl;
	cout << "currNode->currX" << currNode->currX << endl;
	cout << "currNode->currY" << currNode->currY << endl;

	cout << "\n";
	

	//cout << "\n\nnode date = " << absCol << "\n\n";

	//mesure the positions
	updatePositions__private(currNode->left, level + 1, col << 1);
	updatePositions__private(currNode->right, level + 1, (col << 1)|1);
}

void Node::connectWithChildren() {
	glColor3f(nodeSrokeClolor.r, nodeSrokeClolor.g, nodeSrokeClolor.b);
	glLineWidth(5);
	if (left) {
		if (left->isInPosition) {
			glBegin(GL_LINES);
			glVertex2f(currX, currY);
			glVertex2f(left->currX, left->currY);
			glEnd();

		}
		
	}
	if (right) {
		if (right->isInPosition) {
			glBegin(GL_LINES);
			glVertex2f(currX, currY);
			glVertex2f(right->currX, right->currY);
			glEnd();
		}

	}
	
}


void drawText(double x, double y, Color cc, string str, void *font) {
	glColor3f(cc.r, cc.g, cc.b);
	
	int j = str.length();

	double textWidth = 0;

	for (int i = 0; i < j; i++) {
		textWidth += glutBitmapWidth(font, str[i]);
	}

	glRasterPos2f(x - textWidth/2, y - 4);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(font, str[i]);
		
	}
}
void drawCircle(double x, double y, double r) {
	
	glColor3f(nodeBGClolor.r, nodeBGClolor.g, nodeBGClolor.b);
	int iterations = 500;
	glBegin(GL_POLYGON);
	for (int i = 0; i < iterations; i++) {
		double currX = r * cos(2 * PI*(i / (iterations * 1.0)));
		double currY = r * sin(2 * PI*(i / (iterations * 1.0)));
		glVertex2f(x + currX, y + currY);
	}
	glEnd();
	glColor3f(nodeSrokeClolor.r, nodeSrokeClolor.g, nodeSrokeClolor.b);
	glBegin(GL_LINE_LOOP);
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

	
	tree.draw();
	addButton.draw();
	deleteButton.draw();

	if (state.addModalOpenned) {
		addModal.draw();
		closeButton.draw();
		addModal__submitButton.draw();
	}
	else if (state.deleteModalOpenned) {
		deleteModal.draw();
		closeButton.draw();
		deleteModal__submitButton.draw();
	}

	if (abs(nodeRadius - nodeCurrentRadius) > nodeRadiusStep) {
		if (nodeRadius > nodeCurrentRadius)
			nodeCurrentRadius += nodeRadiusStep;
		else
			nodeCurrentRadius -= nodeRadiusStep;
	}

	glFlush();
}


void handleResize(int width, int height) {
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // don't resize the window 
}

void main(int argc, char** argv)
{

	/*
	addModal.inputText = "11";
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
	tree.print();*/

	
	//tree.update();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Binary Search Tree Visualization");
	initGL();
	glutReshapeFunc(handleResize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(handleKeypress);
	glutDisplayFunc(mainLoop);
	glutIdleFunc(mainLoop);
	glutMainLoop();


}
bool Button::checkForMouseClick(int mouseX, int mouseY) {
	/*
	cout << "//////////\n";
	cout << "mouseX = " << mouseX << endl;
	cout << "mouseY = " << mouseY << endl;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "width = " << width << endl;
	cout << "height = " << height << endl;*/
	if (isVisible
		&& mouseX >= x - width / 2
		&& mouseX <= x + width / 2
		&& mouseY >= y - height / 2
		&& mouseY <= y + height / 2
		) {
		buttonClicked();
		return true;
	}

	return false;
}

void Button::buttonClicked() {
	cout << "button clicked = " << name << endl;
	if (name == "ADD") {
		state.addModalOpenned = true;
		addModal__submitButton.isVisible = true;
		closeButton.isVisible = true;
	}
		

	else if (name == "DELETE") {
		state.deleteModalOpenned = true;
		deleteModal__submitButton.isVisible = true;
		closeButton.isVisible = true;
	}
	else if (name == "CLOSE")
		closeAllModals();
	
	else if (name == "ADD NODE") {
		if (addModal.inputText != "") {
			tree.insert(stoi(addModal.inputText));
			closeAllModals();
		}
			
	}
	else if (name == "DELETE NODE") {
		if (deleteModal.inputText != "") {
			tree.deleteNode(stoi(deleteModal.inputText));
			closeAllModals();
		}
			
	}


}
void mouse(int button, int state, int x, int y) {
	y = WINDOW_HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		addButton.checkForMouseClick(x, y);
		closeButton.checkForMouseClick(x, y);
		addModal__submitButton.checkForMouseClick(x, y);
		deleteButton.checkForMouseClick(x, y);
		deleteModal__submitButton.checkForMouseClick(x, y);
	}
}
void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	switch (key) {
	case 27: //Escape key
		exit(0); //Exit the program
	}

	if (state.addModalOpenned) {
		if (key >= '0' && key <= '9') {
			addModal.inputText += key;
		}
		if (key == 8) {
			addModal.inputText = (addModal.inputText).substr(0, (addModal.inputText).size() - 1);
		}
	}
	else if (state.deleteModalOpenned) {
		if (key >= '0' && key <= '9') {
			deleteModal.inputText += key;
		}
		if (key == 8) {
			deleteModal.inputText = (addModal.inputText).substr(0, (addModal.inputText).size() - 1);
		}
	}
}
void closeAllModals() {
	addModal.close();
}

void Modal::close() {
	state.addModalOpenned = false;
	addModal__submitButton.isVisible = false;
	addModal.inputText = "";

	state.deleteModalOpenned = false;
	deleteModal__submitButton.isVisible = false;
	deleteModal.inputText = "";

	closeButton.isVisible = false;
}
void Modal::showInputText() {
	drawText(x, y + 40, modalTexColor,  inputText, GLUT_BITMAP_HELVETICA_18);
}