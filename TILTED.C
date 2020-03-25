#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#include "types.h"
#include "events.h"
#include "renderer.h"
#include "model.h"
#include "raster.h"


int main() 
{
	
	struct Block block;
	struct Model model;
	UINT16 *base = Physbase();

	block.x = 50;
	block.y = 50;
	block.speed = 0;
	block.length = 100;
	
	model.fillLevel = 0;
	
	model.blocks[model.fillLevel] = &block;
	model.fillLevel++;
	
	fill_screen(base, WHITE);
	render(&model, base);

	return 0;
}