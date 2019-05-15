#include <stdlib.h>
#include <stdbool.h>

//variable sized integer array
//TODO redundant?
typedef int * ant_position_t;

//Two degrees of expressability, generally rotation for 3 dimensional motion
typedef struct ant_orientation_t ant_orientation_t;

//Should represent a single ant on 2D or 3D grid
typedef struct ant_t ant_t;

typedef struct ant_cell_t ant_cell_t;

typedef struct ant_grid_t ant_grid_t;

struct ant_orientation_t
{

	int x;
	int y;

};

struct ant_t
{

	ant_orientation_t orientation;
	ant_position_t position;
	size_t tuple_size;
	long long int pos[];

};

struct ant_cell_t
{

	ant_position_t position;
	void (* rule)(ant_cell_t *, ant_t *);
	int state;

	//TODO array
	ant_cell_t * north;
	ant_cell_t * south;
	ant_cell_t * east;
	ant_cell_t * west;

};

struct ant_grid_t
{

	ant_t * ants;
	ant_cell_t * origin;

};

ant_t * zero_ant_position(ant_t *, size_t, bool);

size_t ant_position_tuple_size(ant_t *);

ant_orientation_t generate_orientation(int x, int y);

ant_grid_t new_grid(ant_cell_t * origin);

ant_cell_t new_cell_empty();

