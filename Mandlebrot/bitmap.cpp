#include "bitmap.h"


bitmap::bitmap(int width, int height, std::string name) : width(width), height(height)  //construct and initailize
{ 
	map.open(name, std::ios::out | std::ios::binary); 
	currentHeight = currentWidth = 1; 
}

int bitmap::addHeader() //header
{
	unsigned int bmpSize, dataSize;
	dataSize = (width * height)*3 + ((width *3)%4)*height;
	bmpSize = dataSize + 54;
	if (bmpSize > 4294967295) //4294967295 = max number representable by 32 bits (i.e. the number of bits allowed for in the header)
	{
		std::cout << "Image too large, reduce size"; //complain if the user is absurd and wants a 4gb image, go use JPG or something you fool
		return -1;
	}
	for (int i = 0; i < 4; i++)
	{
		header[2 + i] = (char)((bmpSize >> i*8) & (0x000000FF)); //shifty bits and bitwise ands get you from big endian to little endian
	}
	for (int i = 0; i < 4; i++)
	{
		header[0x12 + i] = (char)((width >> i*8) & (0x000000FF)); //how shifty
	}
	for (int i = 0; i < 4; i++)
	{
		header[0x16 + i] = (char)((height >> i*8) & (0x000000FF)); //watch out for these bits, they be shiftin all around
	}
	for (int i = 0; i < 4; i++)
	{
		header[0x22 + i] = (char)((dataSize >> i*8) & (0x000000FF));
	}
	map.write(&header[0], header.size()); //and finally, dump the header into the file
	
	return 0;
}

void bitmap::addPix(color c) //put pixel into map
{
	char zero = 0; //annoying that this is necessary
	map.write((char *)&(c.blue), sizeof(char)); //put the blue in
	map.write((char *)&(c.green), sizeof(char)); //put the green in
	map.write((char *)&(c.red), sizeof(char)); //put the red in
	if (currentWidth == width) //check for end of line, 1 for PROGRESS BAR!!!, but more importantly for padding
	{
		if (currentHeight % 20 == 0) //PROGRESS BAR!!!!
		{
			int barwidth = 50; //PROGRESS BAR!!!!
			float progress = (float)currentHeight / height; //PROGRESS BAR!!!!
			std::cout << "Writing to file: ["; //PROGRESS BAR!!!!
			int pos = barwidth * progress; //PROGRESS BAR!!!!
			for (int i = 0; i < barwidth; ++i) { //PROGRESS BAR!!!!
				if (i < pos) std::cout << "="; //PROGRESS BAR!!!!
				else if (i == pos) std::cout << ">"; //PROGRESS BAR!!!!
				else std::cout << " "; //PROGRESS BAR!!!!
			} //PROGRESS BAR!!!!
			std::cout << "] " << int(progress * 100.0) << " %\r"; //PROGRESS BAR!!!!
			std::cout.flush(); //PROGRESS BAR!!!!
		}
		currentWidth = 1;
		currentHeight++;
		if ((width * 3) % 4 != 0) //padding
		{
			for (int i = 0; i < abs(((width * 3) % 4) - 4); i++)
			{
				map.write(&zero/*honestly here, fstream, why the heck can't i just put a '0'*/, sizeof(char));
			}
		}
	}
	else
	{
		currentWidth++; //increment width since we aren't at the end of a line
	}
}

void bitmap::closeBmp() //say goodbye to the bitmap \( ._.)
{
	map.close();
}

