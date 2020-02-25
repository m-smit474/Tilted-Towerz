#include "raster.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define HEIGHT 25
#define XOR 2
#define SOLID 0xFFFF
#define BITS_IN_BYTE 8

/*void plot_something_1(UINT16 *base, int x, int y, ...) */
/*{ */
	/* [TO DO] delete this example function */
/*} */

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

void clear_screen()
{
	disable_cursor();					/* hide cursor */
	printf("\033E\033f\n");				/* Blank Screen */
	linea0();
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}

void plot_hline (UINT16 *base, int y, int x1, int x2)
{
UINT16 p1, p2;
int row1, row2, i;
int shift_F, shift_B;
row1 = x1 / BITS_IN_BYTE;
row2 = x2 / BITS_IN_BYTE;
shift_F = x1 >> 3;
shift_B = (BITS_IN_BYTE - 1) - (x2 % (BITS_IN_BYTE - 1));
if (row1 == row2)
{
p1 = SOLID >> shift_F;
p1 = SOLID << shift_B;
*(base + y * 80 + row1) = p1;
}
else
{
p1 = SOLID >> shift_F;
p2 = SOLID << shift_B;
*(base + y * 80 + row1) = p1;
for (i = row1 + 1; i < row2; i++)
{
*(base + y * 80 + i) = SOLID;
}
*(base + y * 80 + row2) = p2;
}
return;
}
