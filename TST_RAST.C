#include <osbind.h>
#include "raster.h"

int main()
{
	/*void *base = Physbase();

	plot_something_1(base, 100, 100);
	plot_something_2(base, 200, 200);

	draw_block(base, 100, 100, 150);*/

	UINT16 *base = Physbase();
	
	fill_screen(base, 0);

	draw_block(base, 50, 50, 100);
	
	

	return 0;
}
