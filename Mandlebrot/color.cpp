#include "color.hpp"
//all of the code in this file was taken from stack overflow: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
//this code converts a color described in HSV to a color described in RGB and was slightly modified by me to make it fit with my program
color color::hsv2rgb(hsv in)
{
	double      hh, p, q, t, ff;
	long        i;
	color       out;



	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.red = in.v;
		out.green = in.v;
		out.blue = in.v;
		return out;
	}
	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.red = (unsigned char)in.v;
		out.green = (unsigned char)t;
		out.blue = (unsigned char)p;
		break;
	case 1:
		out.red = (unsigned char)q;
		out.green = (unsigned char)in.v;
		out.blue = (unsigned char)p;
		break;
	case 2:
		out.red = (unsigned char)p;
		out.green = (unsigned char)in.v;
		out.blue = (unsigned char)t;
		break;

	case 3:
		out.red = (unsigned char)p;
		out.green = (unsigned char)q;
		out.blue = (unsigned char)in.v;
		break;
	case 4:
		out.red = (unsigned char)t;
		out.green = (unsigned char)p;
		out.blue = (unsigned char)in.v;
		break;
	case 5:
	default:
		out.red = (unsigned char)in.v;
		out.green = (unsigned char)p;
		out.blue = (unsigned char)q;
		break;
	}
	return out;
}
