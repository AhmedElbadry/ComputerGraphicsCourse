#pragma once
void drawCircle(double x, double y, double r);
void drawText(double x, double y, const char *string);
void mouse(int button, int state, int x, int y);
void closeAllModals();
struct Color{
	double r, g, b;
	Color();
	Color(double rr, double gg, double bb);
};

struct State {
	bool addModalOpenned = false;
	bool deleteModalOpenned = false;
	bool addNodeTransition = false;
};
