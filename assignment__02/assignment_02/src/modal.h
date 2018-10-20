#pragma once
#include"global.h"
#include<string>
#include"button.h"
using namespace std;

class Modal
{
public:
	Modal(string nn, double xx, double yy, double ww, double hh, Color cc);
	string name;
	double x;
	double y;
	double width;
	double height;
	Color color;

	string inputText;

	void draw();
	void updateInputText(string inputText);
	void close();
	void showInputText();
private:

};

