#include "model.h"
#include "raster.h"
#include <stdio.h>

void move_block_h(struct Block *block)
{
	block->x += block->delta_x;
}

void move_block_v(struct Block* block)
{
	block->y += block->delta_y;

	/*colliosion detection here*/
}