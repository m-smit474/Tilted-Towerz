#ifndef MODEL_H
#define MODEL_H

#include "types.h"

struct Block
{
	int x, y;
	int speed;
	int length;
};

struct Model
{
	Block* blocks[20];
	int fillLevel;
};

void move_block_h(struct Block* block);
void move_block_v(struct Block* block);

#endif
