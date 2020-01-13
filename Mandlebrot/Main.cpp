#include "bitmap.hpp"
#include "color.hpp"
#include "mandlebrot.hpp"
#include <complex>
#include <random>
#include <chrono>
#include <vector>


/*
	El disclaimer: This code was commented in the weee hours of the morning, so i had to entertain myself somehow
*/

int main()
{
	unsigned int seed;

	seed = std::chrono::system_clock::now().time_since_epoch().count(); //seed and initalize the RNG
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(1, 3);

	std::vector<color> colors; //vector of colors

	int barwidth = 50, paletteIndex = distribution(generator), WIDTH, HEIGHT, userPalette;
	double progress = 0.0, posx, negx, posy, negy;
	std::string name;
	std::cout << "Enter your desired width of Mandelbrot set "; //all sorts of prompts
	std::cin >> WIDTH;
	std::cout << "Enter your desired positive x bound ";
	std::cin >> posx;
	std::cout << "Enter your desired negative x bound ";
	std::cin >> negx;
	std::cout << "Enter your desired positive y bound ";
	std::cin >> posy;
	std::cout << "Enter your desired negative y bound ";
	std::cin >> negy;
	HEIGHT = int(WIDTH * ((posy - negy) / (posx - negx)));
	std::cout << "Enter a palette index (1-3) or zero for random ";
	std::cin >> userPalette;
	std::cout << "Name your file (don't forget to add .bmp to the end) ";
	std::cin >> name;
	if (userPalette != 0)
	{
		paletteIndex = userPalette;
	}

	bitmap map1(WIDTH, HEIGHT, name); //initalize the bitmap and mandelbrot
	mandlebrot mbrot(WIDTH, HEIGHT);

	map1.addHeader(); 
	/*
								   /=//==//=/    \
								  |=||==||=|      |
								  |=||==||=| ~- , |
								  |=||==||=| ^.`; |
								  \=\\==\\=\`=.:
								   `"""""""`^ - , `.
												`.~, '
												',~^:, el header
												`.^; `.
												^-.~= ; .
												`.^.:`.

						                _.                              _______
						          __.--'  |             ____...,---'''''     .'''-.
						      _,-'        \ ____...--'''                     | '   '-._
						   ,-'             |                                 |  \      -.
						,-'                '                                 |   '       `\
						|                    \                               .'    '   _,._/
						|                     \                              |      '  \
						|                     \                              |       \  '
						||                     \                             |        \<
						|\                      \                           |          \|
						|'.                     \                           /           |
						| |                      \                         |            '
						| '.                      |                  ____,..             \
						|  |                       \__,...-----''''''       `.            |
						|  '.                      \                          \           '
						|   |                       \    424d      0100        `           \
						|   '                        \   00000000  1800         `           |
						|    |                        \  00        00000000      \          \
						|    '.                       '  00        00000000       \          \
						|     \                        \ 36000000  130b0000        \       _,|
						|      |                        \28000000  130b0000         \ _,.--  |
						|      '.                       ,00000000  00000000     _,.-'       |
						'       \                  _,.-''00000000  00000000_.,-''            |
						  |       |             _.-'                _,.,--'                   |
						  \        \        _.-'           __,.,--''                          |
						  '        `.    ,-'      __..---''                                   |
						  '         \ ,-'___..,--'                                            '
						  \         -'''                                                      .
						   .        |     _     _____ ____  ____  _____ ____                  ,
						    |       |    / \ /|/  __//  _ \/  _ \/  __//  __\                 |   
						    '       |    | |_|||  \  | / \|| | \||  \  |  \/|                 |
						     \      |    | | |||  /_ | |-||| |_/||  /_ |    /                 |
						      \     |    \_/ \|\____\\_/ \|\____/\____\\_/\_\                 |
						       \    |                                                  __,.-''
					         	\   |                                         __,..-''
						         \  |                              ___..--'''     
						          \ |                     ___,.--''
					      	       \|        ____...,--'''
						            '_..,--''
	*/



	for (int i = 1; i < HEIGHT + 1; i++)
	{
		for (int j = 1; j < WIDTH + 1; j++)
		{
			std::complex<int> a(i, j);
			colors.push_back(mbrot.genPix(j, i, 1000, paletteIndex, posx, negx, posy, negy)); //generate colors for all the pixels
		}
		if (i % 20 == 0) //PROGRESS BAR!!! only works on windows :(
		{
			progress = (float)i / HEIGHT;
			std::cout << "Calculation: [";
			int pos = (int)(barwidth * progress);
			for (int i = 0; i < barwidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			std::cout << "] " << int(progress * 100.0) << " %\r";
			std::cout.flush();
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < colors.size(); i++) //dump pixels to file, and add padding if needed
	{
		map1.addPix(colors[i]);
	}
	map1.closeBmp();
}
