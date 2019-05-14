#include "anttype.h"
#include "string.h"

void zero_ant_position(ant_t * ant, size_t size, bool allocated)
{
	
	if (allocated) free(ant->position);
	//ant->position = memset(realloc(ant->position, sizeof(int) * size), 0, size * sizeof(int));
	reallocarray(ant->position, size, sizeof(int));
	ant_position_t position = ant->position;
	memset(position, 0, sizeof(position));
	//printf("zero here\nsize var: %d ----- sizeof alloc: %d\n",size, sizeof(ant->position));
	
}

size_t ant_position_tuple_size(ant_t * ant)
{
	
	//printf("%d\n", sizeof(ant->position));
	return sizeof(ant->position) / sizeof(ant->position[0]);
	
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

