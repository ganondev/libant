#include "anttype.h"
#include "string.h"

ant_t * zero_ant_position(ant_t * ant, size_t size, bool allocated)
{
	
//	ant->tuple_size = size;
//	if (allocated) free(ant->position);
//	printf("%d\n", sizeof(ant->position));
//	void * alloc = realloc(ant->position, sizeof(int) * size);
//	void * alloc = realloc(ant->pos, sizeof(int) * size);
//	puts("here");
//	printf("%d %d %d\n", sizeof(alloc), sizeof(int) * size, sizeof(ant->position));
//	memset(alloc, 0, sizeof(int) * size);
//	printf("%d %d\n", sizeof(ant->position), sizeof(alloc));
	ant = realloc(ant, sizeof(ant_t) + size * sizeof(int));
	memset(ant->pos, 0, size * sizeof(int));
	ant->tuple_size = size;
	
	return ant;
	
}

size_t ant_position_tuple_size(ant_t * ant)
{
		
//	return sizeof(ant->pos) / sizeof(ant->pos[0]);
	return ant->tuple_size;
	
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

