#pragma once

#include <complex>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <cmath>
#include "color.h"
class bitmap
{
private:
	int width;
	int height;
	int currentWidth;
	int currentHeight;
	std::fstream map;
	std::array<char, 54> header = {
		0x42, 0x4d, //ID field
		0, 0, 0, 0, //size of file (edited later)
		0, 0, //"Unused" (according to wikipedia
		0, 0, // same as above
		0x36, 0, 0, 0, //offset of primary pixel array
		0x28, 0, 0, 0, //size of DIB header
		0, 0, 0, 0, //width in pixels
		0, 0, 0, 0, //height in pixels
		0x01, 0, //number of color planes
		0x18, 0, //24 bits per pixel
		0, 0, 0, 0, //pixel compression (none)
		0, 0, 0, 0, //raw bitmap data
		0x13, 0x0b, 0, 0, //2835 pixels per meter
		0x13, 0x0b, 0, 0, //as above
		0, 0, 0, 0, //all colors (0)
		0, 0, 0, 0 }; //all colors important (0)
public:
	bitmap(int width, int height, std::string name); //constructor
	int addHeader(); //dump header onto file
	void addPix(color); //add pixel, using padding at the end of lines when necessary
	void closeBmp(); //close file
};

