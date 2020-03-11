#include "model.h"
#include "raster.h"
#include <stdio.h>

#define DROP_SPEED 5

void move_block_h(struct Block *block)
{
	block->x += block->speed;
}

void move_block_v(struct Block* block)
{
	block->y += block->DROP_SPEED;

	/*colliosion detection here*/
}

void update_size()
{
	
}