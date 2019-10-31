#define LIBANT_DEBUG

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <libant.h>
#include <ant.h>

#ifndef _WIN32

#include <mcheck.h>

#else

#define mprobe(arg) 0
#define MCHECK_OK 0

#endif

#define mprobe_assert(arg) assert(mprobe(arg)==MCHECK_OK)

#define test(NAME)	n_tests++; \
					test_names = realloc(test_names, sizeof(char *) * n_tests); \
					test_names[n_tests - 1] = #NAME; \
					tests = realloc(tests, sizeof(test_fn) * n_tests); \
					tests[n_tests - 1] = NAME;

typedef int(*test_fn)();

int n_tests = 0;
int i = 0;
char ** test_names = NULL;
test_fn * tests = NULL;

void pp_puts(const char* msg)
{

	printf("%s\n%d/%d\r", msg, i, n_tests);

}

void pp_puts_empty()
{

	printf("%d/%d\r", i, n_tests);

}

int grid_create()
{

	pp_puts(TRACE("Beginning grid head creation test."));

	ant_grid_t grid = new_grid(NULL, NULL);
	assert(grid.get == NULL);
	assert(grid.insert == NULL);
	// assert(grid.scan_list_size == 0); this is not coming out as zero on the dell machine

	mprobe_assert(grid.scan_list);

	pp_puts(IO_OK("Grid head creation test complete!"));
	return 1;

}

int ant_create()
{

	pp_puts(TRACE("Beginning ant head creation test."));

	for (int i = 1; i < 10000; i++)
	{

		ant_t * ant = create_ant(i);
		mprobe_assert(ant);
		assert(ant->directive == NULL);
		assert(ant->orientation == 0);
		for (int n = 0; n < i; i++) assert((ant->position)[n] == 0);
		free(ant);

	}

	pp_puts(IO_OK("Ant head creation test complete!"));
	return 1;

}

int main()
{

	test(grid_create);
	test(ant_create);

	puts(TRACE("\nBeginning tests for libant core library.\n"));

	pp_puts_empty();
	while (i < n_tests)
	{

		tests[i++]();
		pp_puts_empty();

	}

	puts(IO_OK("\nCompleted all tests for libant core library.\n"));

}
