#ifndef RASTER_H
#define RASTER_H

#define HEIGHT 15
#define XOR 2
#define SOLID 0xFFFF
#define BITS_IN_BYTE 8
#define BYTES_PER_SCREEN 32000
#define BLACK -1
#define WHITE 0

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */

/*void plot_something_1(UINT16 *base, int x, int y, ...); */
/*void plot_something_2(UINT32 *base, int x, int y, ...); */

void fill_screen (UINT16 *base, char pattern);
void clear_block(UINT16 *base, int y);
void disable_cursor();
void plot_hline (UINT16 *base, int y, int x1, int x2);
void plot_vline (UINT16 *base, int x, int y1, int y2);
void draw_block (UINT16 *base, int x, int y, int length);

#endif
