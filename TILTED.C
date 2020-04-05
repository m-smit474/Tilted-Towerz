#include <stdio.h>
#include <stdlib.h>
#include <linea.h>
#include <osbind.h>

#include "types.h"
#include "events.h"
#include "renderer.h"
#include "model.h"
#include "raster.h"

#define MAX_LENGTH 200

void makeBlock(int x, int y, int speed, int length, struct Block *block);
void addBlock(struct Model *model, struct Block *block);

int main() 
{
	struct Block blocks[20];
	struct Block foundation;
	struct Block block2;
	struct Model model;
	UINT16 *base = Physbase();
	int currentBlock = 0;
	int currentSpeed = 1;
	int previousLevel;
	bool done = false;
	
	/* Instatiate foundation */
	
	makeBlock(220,350,0, MAX_LENGTH, &blocks[currentBlock]);
	
	/* Add foundation to model */
	
	model.fillLevel = 0;
	
	addBlock(&model, &blocks[currentBlock]);
	

	currentBlock++;
	
	
	/* Draw starting scene */
	
	fill_screen(base, WHITE);
	render(&model, base);
	
	/* Enter main game loop */
	/* Moves one block at a time */
	
	while(!done)
	{
		/* Add current block to model */
		makeBlock(0,0,currentSpeed, blocks[currentBlock-1].length, &blocks[currentBlock]);
		addBlock(&model, &blocks[currentBlock]);
		
		/* Enter loop */
		/* Move block horizontally until key pressed */
		while(!Cconis())
		{
			move_block_h(model.blocks[currentBlock]);
			clear_block(base, model.blocks[currentBlock]->y);
			render_block(model.blocks[currentBlock], base);
			Vsync();
			
			/* change direction when it hits walls */
			if(model.blocks[currentBlock]->x <= 0 || model.blocks[currentBlock]->x + model.blocks[currentBlock]->length >= 640)
			{
				model.blocks[currentBlock]->speed *= -1;
			}
		}
		
		/*This is to clear the buffer*/
		Cnecin();

		previousLevel = model.blocks[currentBlock-1]->y;
		/* Enter loop */
		/* Drop block until previous blocks y position (collision) */
		while(!check_collision(model.blocks[currentBlock]->y, previousLevel))
		{
			move_block_v(model.blocks[currentBlock]);
			clear_block(base, model.blocks[currentBlock]->y);
			render_block(model.blocks[currentBlock], base);
			Vsync();
		}

		if (model.blocks[currentBlock]->x > model.blocks[currentBlock - 1]->x + model.blocks[currentBlock - 1]->length)
		{
			done = true;
			break;
		}
			
		if (model.blocks[currentBlock - 1]->x > model.blocks[currentBlock]->x + model.blocks[currentBlock]->length)
		{
			done = true;
			break;
		}

		/*update size of current block*/
		update_size(model.blocks[currentBlock], model.blocks[currentBlock - 1]->x);

		/*make a flash and sound to go with it here*/
		fill_screen(base, WHITE);
		render(&model, base);
		
		/*done = true; /* run once */
		currentBlock++;
	}
	
	/* Blocks have stacked to top of screen or length of block is 0 */

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