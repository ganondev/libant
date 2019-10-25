#include <grid.h>
#include "quadtree/quadtree.h"

ant_grid_t new_grid(grid_getfn getfn, grid_insertfn insertfn)
{

	#ifdef LIBANT_DEBUG
	puts(TRACE("Creating new grid."));
	#endif

	ant_grid_t grid =
	{

		.get = getfn,
		.insert = insertfn,
		.scan_list_size = 0,
		.scan_list = malloc(sizeof(ant_cell_t *))

	};
	return grid;

}
