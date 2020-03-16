#include "events.h"
#include "renderer.h"
#include "model.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#include "types.h"

int main() 
{
	Block block;
	UINT16 *base = physbase();

	block->x = 50;
	block->y = 50;
	block->speed = 0;
	block->length = 50;

	render_block(block, base);

	return 0;
}