#pragma once
void drawCircle(double x, double y, double r);
void drawText(double x, double y, const char *string);

struct Color{
	double r, g, b;
	Color();
	Color(double rr, double gg, double bb);
};