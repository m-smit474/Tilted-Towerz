#include "raster.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

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

void clear_block(UINT16 *base, int y)
{
	/* 80 bytes in a line */
	/* 15 is height of block */
	int start = y * 40;
	int end = start + (40 * 16);
	register int i = start;
	register UINT16 *loc = base;
	
	loc = loc + start;

	while (i++ < end)
		*(loc++) = WHITE;
}

void plot_hline (UINT16 *base, int y, int x1, int x2)
{
	UINT16 p1, p2;
	int row1, row2, i;
	int shift_F, shift_B;
	UINT16* place = base + y * 40;
	
	row1 = x1 / 15;
	row2 = x2 / 15;
	shift_F = x1 % 15;
	shift_B = (15 - 1) - (x2 % 15);
	
	if (row1 == row2)
	{
		p1 = SOLID >> shift_F;
		p2 = SOLID << shift_B;
		*(place + row1) = p1 & p2;
	}
	else
	{
		p1 = SOLID >> shift_F;
		p2 = SOLID << shift_B;
		*(place + row1) = p1;
		for (i = row1 + 1; i < row2; i++)
		{
			*(place + i) = SOLID;
		}
		*(place + row2) = p2;
	}	
	return;
}

void plot_vline(UINT16 *base, int x, int y1, int y2)
{
	int temp;
	UINT16 pattern;
	UINT16* screen_byte;

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

		pattern = 1 << (15 - (x & 15));
		screen_byte = base + y1 * 40 + (x >> 4);
		for (; y1 <= y2; y1++)
		{
			*screen_byte = pattern;
			screen_byte = screen_byte + 40;
		}
	}
	return;
}


