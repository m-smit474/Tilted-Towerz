#include "events.h"
#include "model.h"
#include "raster.h"

bool check_collision(int y, int current_lvl)
{
	bool collision = false;

	if (y + HEIGHT >= current_lvl)
	{
		collision = true;
	}

	return collision;
}
