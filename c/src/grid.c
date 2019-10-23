#include <grid.h>
#include "quadtree/quadtree.h"

ant_grid_t * new_grid(/* TODO pass in tree or function pointer to create tree */)
{

	#ifdef LIBANT_DEBUG
	puts(TRACE("Creating new grid."));
	#endif

	ant_grid_t * grid = calloc(1, sizeof(ant_grid_t));
	grid->scan_list = malloc(sizeof(ant_cell_t *));
	grid->tree = libant_quadtree_create();
	return grid;

}
