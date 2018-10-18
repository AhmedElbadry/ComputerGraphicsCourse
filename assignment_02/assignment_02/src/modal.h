#pragma once
#include"global.h"
#include<string>
#include"button.h"
using namespace std;

class Modal
{
public:
	Modal(string nn, double xx, double yy, double ww, double hh, Color cc, Button colse);
	string name;
	double x;
	double y;
	double width;
	double height;
	Color color;

	string inputText;

	Button close;

	void draw();
	void updateInputText(string inputText);

private:

};

