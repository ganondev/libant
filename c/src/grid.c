#include <grid.h>

void grid_add_ant(ant_grid_t * grid, ant_t * ant)
{

	LOG(printf(TRACELN("Adding ant to scan list with initial size %zu."), grid->scan_list_size));
	grid->scan_list = realloc(grid->scan_list, sizeof(ant_t *) * ++(grid->scan_list_size)); // TODO find alternative, this is unsafe
	LOG(printf(DEBUGLN("Scan list new size: %zu."), grid->scan_list_size));
	grid->scan_list[grid->scan_list_size - 1] = ant;

}

void new_grid(ant_grid_t * grid, grid_getfn getfn, grid_insertfn insertfn)
{

	LOG(puts(TRACE("Creating new grid.")));

	grid->get = getfn;
	grid->insert = insertfn;
	grid->scan_list_size = 0;
	grid->scan_list = NULL;

}
