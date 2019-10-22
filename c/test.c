#define LIBANT_DEBUG

#include "include/standards.h"
#include "include/antmacro.h"
#include "include/anttype.h"
#include <stdio.h>

int test1()
{

	puts(TRACE("Beginning main test 1."));

	ant_grid_t * grid = new_grid();
	printf("%lld %lld\n", grid->tree->root->x, grid->tree->root->y);

	puts(IO_OK("Test 1 complete!"));
	return 1;

}

int main()
{

	puts(TRACE("\nBeginning tests for libant core library.\n"));
	test1();
	puts(IO_OK("\nCompleted all tests for libant core library.\n"));

}
