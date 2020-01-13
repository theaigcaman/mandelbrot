#pragma once
#include "hsv.hpp"
class color
{
public:
	color() {}; //default constructor
	color(unsigned char red, unsigned char green, unsigned char blue) : red(red), green(green), blue(blue) {}; //constructor
	void setRgb(int ired, int igreen, int iblue) { red = ired; blue = iblue; green = igreen; } //set RGB values
	unsigned char red, green, blue; //Data
	static color hsv2rgb(hsv in); //convert HSV to RGB
};

