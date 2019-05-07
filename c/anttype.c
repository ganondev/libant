#include "anttype.h"

ant_orientation_t generate_orientation(int x, int y)
{
	
	ant_orientation_t orient;
	orient.x = x;
	orient.y = y;

	return orient;
	
}

ant_grid_t new_grid(ant_cell_t * origin)
{

	ant_grid_t grid;
	grid.origin = origin;

}