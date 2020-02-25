#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */

/*void plot_something_1(UINT16 *base, int x, int y, ...); */
/*void plot_something_2(UINT32 *base, int x, int y, ...); */

void draw_block(int x, int y, int length);
void plot_line(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short style, short mode);
void clear_screen();
void disable_cursor();
void plot_hline (UINT16 *base, int y, int x1, int x2);

#endif
