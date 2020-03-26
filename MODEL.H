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
	struct Block* blocks[20];
	int fillLevel;
};

void update_size(struct Block* block, int previousLeft);
void move_block_h(struct Block* block);
void move_block_v(struct Block* block);

#endif
