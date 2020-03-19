#include "model.h"
#include "raster.h"
#include "events.h"
#include <stdio.h>

#define DROP_SPEED 5

void move_block_h(struct Block *block)
{
	block->x += block->speed;
}

void move_block_v(struct Block* block)
{
	block->y += DROP_SPEED;
}

void update_size(struct Block* block, int previousLeft)
{
	int displacement = previousLeft - (block->x);
	
	displacement = abs(displacement);
	
	block->length = block->length - displacement;
	
	if(block->x < previousLeft)
	{
		block->x = block->x + displacement;
	}
}