#include <stdlib.h>

#define INTSIZE sizeof(int)

//variable sized integer array
typedef int * position_t;

//Two degrees of expressability, generally rotation for 3 dimensional motion
typedef struct orientation {
	
	int x;
	int y;
	
} orientation_t;

//Should represent a single ant on 2D or 3D grid
typedef struct turmite {
	
	position_t position;
	orientation_t orientation;
	
} turmite_t;

typedef struct cell {

	void (* rule)(struct cell *, turmite_t *);
	int state;

} cell_t;

typedef struct grid {
	
	turmite_t * turmites;
	cell_t ** cells;
	
} grid_t;

orientation_t generateOrientation(int x, int y);

//TODO Function to create cell with some initial state, and determine way to locate cell in grid