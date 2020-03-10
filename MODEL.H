#ifndef MODEL_H
#define MODEL_H

#include "types.h"

struct Block
{
	unsigned int x, y;
	int delta_x, delta y;
};

struct Base
{
	unsigned int x, y;
};

void move_block_h(struct Block* block);
void move_block_v(struct Block* block);

#endif
