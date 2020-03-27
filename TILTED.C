#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#include "types.h"
#include "events.h"
#include "renderer.h"
#include "model.h"
#include "raster.h"

#define MAX_LENGTH 100

void makeBlock(int x, int y, int speed, int length, struct Block *block);
void addBlock(struct Model *model, struct Block *block);

int main() 
{
	
	struct Block foundation;
	struct Block block2;
	struct Model model;
	UINT16 *base = Physbase();
	
	makeBlock(100,176,0, MAX_LENGTH, &foundation);
	makeBlock(0,0,1, MAX_LENGTH, &block2);
	
	/* Add blocks to model */
	
	model.fillLevel = 0;
	
	addBlock(&model, &foundation);
	addBlock(&model, &block2);

	
	/* Draw */
	
	fill_screen(base, WHITE);
	render(&model, base);
	
	while(!Cconis())
	{
		move_block_h(model.blocks[1]);
		clear_block(base, model.blocks[1]->y);
		render(&model, base);
		Vsync();
	}

	return 0;
}

void makeBlock(int x, int y, int speed, int length, struct Block *block)
{
	block->x = x;
	block->y = y;
	block->speed = speed;
	block->length = length;
}

void addBlock(struct Model* model, struct Block *block)
{
	model->blocks[model->fillLevel] = block;
	model->fillLevel++;
}