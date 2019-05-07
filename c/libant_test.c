#include <stdio.h>
#include "anttype.h"

void printlnd(int i)
{
	
	printf("%d\n", i);
	
}

int main() {

	ant_grid_t grid;
	ant_cell_t cell;
	grid.origin = &cell;
	printlnd(grid.origin->state);

}