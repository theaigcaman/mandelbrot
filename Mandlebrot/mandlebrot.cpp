#include "mandlebrot.h"



mandlebrot::mandlebrot(int width, int height) : width(width) , height(height) {} //construction

color mandlebrot::genPix(int xx, int yy, int maxIteration, int paletteIndex, double posx, double negx, double posy, double negy) //get RGB values for a set pixel
{
	double x, x0, y, y0, xtemp;
	int iteration;
	x0 = (double)xx/width*(posx - negx) + negx; //scale pixel in question to the range of the mandelbrot
	y0 = (double)yy/height*(posy - negy) + negy; 
	x = 0;
	y = 0;
	iteration = 0;
	color black(0, 0, 0); //for later use
	while (x*x + y*y < 2*2 && iteration < maxIteration) //while x^2 + y^2 < 4 and iteration is less than the max
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x*y + y0;
		x = xtemp;
		iteration++; //do one iteration of the Mandelbrot set
	}
	
	if (paletteIndex == 1) //got this off the internet, is supposed to look somewhat like the sets on Wikipedia
	{
		if (iteration < maxIteration && iteration > 0) {
			int i = iteration % 16;
			color mapping[16];
			mapping[0].setRgb(66, 30, 15);
			mapping[1].setRgb(25, 7, 26);
			mapping[2].setRgb(9, 1, 47);
			mapping[3].setRgb(4, 4, 73);
			mapping[4].setRgb(0, 7, 100);
			mapping[5].setRgb(12, 44, 138);
			mapping[6].setRgb(24, 82, 177);
			mapping[7].setRgb(57, 125, 209);
			mapping[8].setRgb(134, 181, 229);
			mapping[9].setRgb(211, 236, 248);
			mapping[10].setRgb(241, 233, 191);
			mapping[11].setRgb(248, 201, 95);
			mapping[12].setRgb(255, 170, 0);
			mapping[13].setRgb(204, 128, 0);
			mapping[14].setRgb(153, 87, 0);
			mapping[15].setRgb(106, 52, 3);
			return mapping[i];
		}
		else return black; //used later
	}
	if (paletteIndex == 2) //simple grayscale with a square root to bias the larger numbers
	{
		if (iteration > maxIteration)
		{
			return black;
		}
		double factor = sqrt((double)iteration / maxIteration);
		unsigned char ofactor = (unsigned char)(factor * 255);
		color out(ofactor, ofactor, ofactor);
		return out;
	}
	if (paletteIndex == 3) //smack (iteration/maxIteration) with a natural log (none of that base ten stuffs) and then scale up to a max value of 360 (for HSV color)
	{
		hsv pixel;
		pixel.h = (int)(360.0 * (log(iteration) / log(maxIteration)));
		pixel.s = 255;
		pixel.v = (iteration < maxIteration) ? 255 : 0;
		return color::hsv2rgb(pixel); //and convert to an RGB color and return it
	}
	return black; //poor lonely return statement never gets called, but does shut the compiler up about not all paths return a value >:|
}
