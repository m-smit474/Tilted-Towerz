#include "raster.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define HEIGHT 25
#define XOR 2
#define SOLID 0xFFFF

void plot_something_1(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

void draw_block(int x, int y, int length)
{
	length = 150;
	
	plot_line(x, y, x, y + HEIGHT, SOLID, XOR); /* Left Side */
	plot_line(x, y, x + HEIGHT, y, SOLID, XOR); /* Top Side */
	plot_line(x + length, y, x + length, y + HEIGHT, SOLID, XOR); /* Right Side */
	plot_line(x, y + HEIGHT, x + length, y + HEIGHT, SOLID, XOR); /* Bottom Side */
}

void plot_line(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short style, short mode)
{
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}
