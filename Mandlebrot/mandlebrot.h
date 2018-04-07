#pragma once
#include "color.h"
#include <complex>

class mandlebrot
{
private:
	int width; //width in pixels of the desired set
	int height; //height
public:
	mandlebrot(int width, int height); //constructor
	color genPix(int xx, int yy, int maxIteration, int paletteIndex, double posx, double negx, double posy, double negy); //function to generate a pixel at a specified index
};

