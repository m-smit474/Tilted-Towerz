#include "raster.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>


/*void plot_something_1(UINT16 *base, int x, int y, ...) */
/*{ */
	/* [TO DO] delete this example function */
/*} */

void draw_block(UINT16 *base, int x, int y, int length)
{
	plot_vline(base, x, y, y + HEIGHT); 		 /* Left Side */
	plot_vline(base, x + length, y, y + HEIGHT); /* Right Side */
	plot_hline(base, y, x, x + length); 		 /* Top Side */
	plot_hline(base, y + HEIGHT, x, x + length); /* Bottom Side */
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}

void fill_screen(UINT16 *base, char pattern)
{
	register int i = 0;
	register UINT16 *location = base;
	
	while (i++ < BYTES_PER_SCREEN)
		*(location++) = pattern;
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

void plot_vline (UINT16 *base, int x, int y1, int y2)
{
	int temp;
	UINT16 pattern;
	UINT16 *screen_byte;
	
	if (x >= 0 && x < 640)
	{
		if (y1 > y2)
		{
		temp = y1;
		y1 = y2;
		y2 = temp;
		}
		if (y1 < 0) y1 = 0;
		if (y2 > 399) y2 = 399;
		
		pattern = 1 << (7 - (x & 7));
		screen_byte = base + y1 * 80 + (x >> 3);
		for ( ; y1 <= y2; y1++)
		{
		*screen_byte = pattern;
		screen_byte = screen_byte + 80;
		}
	}
	return;
}
