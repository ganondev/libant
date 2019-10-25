#define LIBANT_DEBUG

#include <stdio.h>
#include <stdlib.h>

#include <libant.h>

int grid_create()
{

	puts(TRACE("Beginning grid head creation test."));

	ant_grid_t grid = new_grid(NULL, NULL);
	assert(grid.get == NULL);
	assert(grid.insert == NULL);
	assert(grid.scan_list_size = 0);

	puts(IO_OK("Grid head creation test complete!"));
	return 1;

}

int main()
{

	puts(TRACE("\nBeginning tests for libant core library.\n"));
	grid_create();
	puts(IO_OK("\nCompleted all tests for libant core library.\n"));

}
