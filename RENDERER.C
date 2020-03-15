#include "renderer.h"
#include "model.h"
#include "raster.h"

void render(const struct Model *model, UINT16 *base)
{
	int currentBlock = 0;
	
	while(currentBlock < model->fillLevel)
	{
		render_block(model->blocks[currentBlock]);
		
		currentBlock++;
	}
	
}

void render_block(const struct *Block block, UINT16 *base)
{
	draw_block(base, block->x, block->y, block->length);
}