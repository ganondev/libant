#include <grid.h>
#include "quadtree/quadtree.h"

ant_grid_t * new_grid()
{

	ant_grid_t * grid = calloc(1, sizeof(ant_grid_t));
	grid->tree = libant_quadtree_create();
	return grid;

}
