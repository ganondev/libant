#include "anttype.h"
#include "string.h"

ant_t * zero_ant_position(ant_t * ant, size_t size, bool allocated)
{
	
	ant = realloc(ant, sizeof(ant_t) + size * sizeof(long long int));
	memset(ant->pos, 0, size * sizeof(long long int));
	ant->tuple_size = size;
	
	return ant;
	
}

ant_orientation_t generate_orientation(int x, int y)
{
	
	ant_orientation_t orient;
	orient.x = x;
	orient.y = y;

	return orient;
	
}

ant_grid_t new_grid(ant_cell_t * origin)
{

	ant_grid_t * grid = grid = calloc(1, sizeof(ant_grid_t));
	grid->origin = origin;
	return * grid;

}

ant_cell_t new_cell_empty()
{

	ant_cell_t * cell = calloc(1, sizeof(ant_cell_t));
	return * cell;

}

