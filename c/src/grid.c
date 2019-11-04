#include <grid.h>

void grid_add_ant(ant_grid_t * grid, ant_t * ant)
{

	#ifdef LIBANT_DEBUG
	printf(TRACELN("Adding ant to scan list with initial size %zu."), grid->scan_list_size);
	#endif
	grid->scan_list = realloc(grid->scan_list, sizeof(ant_t *) * ++(grid->scan_list_size)); // TODO find alternative, this is unsafe
	#ifdef LIBANT_DEBUG
	printf(DEBUGLN("Scan list new size: %zu."), grid->scan_list_size);
	#endif
	grid->scan_list[grid->scan_list_size - 1] = ant;

}

void new_grid(ant_grid_t * grid, grid_getfn getfn, grid_insertfn insertfn)
{

	#ifdef LIBANT_DEBUG
	puts(TRACE("Creating new grid."));
	#endif

	grid->get = getfn;
	grid->insert = insertfn;
	grid->scan_list_size = 0;
	grid->scan_list = NULL;

}
