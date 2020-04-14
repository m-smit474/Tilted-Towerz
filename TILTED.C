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
#define MAX_BLOCKS 20
#define MAX_SPEED 10

void makeBlock(int x, int y, int speed, int length, struct Block *block);
void addBlock(struct Model *model, struct Block *block);
void playSound();

int main() 
{
	struct Block blocks[MAX_BLOCKS];
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
	
	disable_cursor();
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
		
		if (currentBlock == MAX_BLOCKS)
		{
			done = true; 
			break;
		}

		/*Play collision sound*/
		playSound();

		/*update size of current block*/
		update_size(model.blocks[currentBlock], model.blocks[currentBlock - 1]->x);

		/*make a flash*/
		fill_screen(base, WHITE);
		render(&model, base);
		
		/* Increment */
		currentBlock++;
		if (currentSpeed < MAX_SPEED)
			currentSpeed++;
	}
	
	/* Blocks have stacked to top of screen or length of block is 0 */

	return 0;
}

void playSound()
{
	int count = 0;

	volatile char* PSG_reg_select = 0xFF8800;
	volatile char* PSG_reg_write = 0xFF8802;

	long old_ssp = Super(0);

	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write = 100;

	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 */
	*PSG_reg_write = 1;

	*PSG_reg_select = 7;		/* enable channel A on mixer */
	*PSG_reg_write = 0x3E;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write = 10;

	while (count != 4000) {     /* tone now playing */
		count++;
	}

	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write = 0;

	Super(old_ssp);
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