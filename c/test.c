#define LIBANT_DEBUG

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <libant.h>

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
	assert(grid.scan_list_size == 0);

	mprobe_assert(grid.scan_list);

	pp_puts(IO_OK("Grid head creation test complete!"));
	return 1;

}

int main()
{

	test(grid_create);

	puts(TRACE("\nBeginning tests for libant core library.\n"));

	pp_puts_empty();
	while (i < n_tests)
	{

		tests[i++]();
		pp_puts_empty();

	}

	puts(IO_OK("\nCompleted all tests for libant core library.\n"));

}
