#ifndef LIBANT_ANTTYPE_H
#define LIBANT_ANTTYPE_H

#include "../src/quadtree/quadtree.h"

#include <stdlib.h>
#include <stdbool.h>

//Should represent a single ant on 2D or 3D grid
typedef struct ant_t ant_t;

typedef struct ant_cell_t ant_cell_t;

typedef struct ant_grid_t ant_grid_t;

struct ant_t
{

	unsigned int orientation;
	size_t tuple_size;
	void (* directive)(ant_t *, ...);
	long long int position[];

};

struct ant_cell_t //TODO merge with data structure cells
{

	//TODO Same as ant_t: C99 VLA? 
	long long int * position;
	void (* rule)(ant_cell_t *, ant_t *); //TODO change to int for error checking
	int state;

};

struct ant_grid_t // eventually other data structures should be inlined castable extensions of this
{

	libant_quadtree_t * tree; //TODO will need to be heavily generalized

	//TODO void * (* get)(INT x, INT y)
	//TODO void (* insert)(INT x, INT y, void * value)

	ant_t * ants;
	ant_cell_t * scan_list;

};

inline void * get(ant_grid_t * grid, INT x, INT y)
{

	return qt_get(grid->tree, x, y);

}

inline void insert(ant_grid_t * grid, INT x, INT y, void * value)
{

	qt_insert(grid->tree, x, y, value);

}

#ifndef _WIN32
inline
#endif
ant_t * create_ant(size_t);

inline void zero_ant_position(ant_t *);

inline ant_t * resize_ant_position(ant_t *, size_t);

ant_grid_t * new_grid(/*ant_cell_t * origin*/); //TODO bring it back but make it generic

#endif
