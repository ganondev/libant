#include "anttype.h"
#include "string.h"

ant_t * zero_ant_position(ant_t * ant, size_t size)
{
	
	ant = realloc(ant, sizeof(ant_t) + size * sizeof(long long int));
	memset(ant->position, 0, size * sizeof(long long int));
	ant->tuple_size = size;
	
	return ant;
	
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

