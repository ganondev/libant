#ifndef LIBANT_ANTTYPE_H
#define LIBANT_ANTTYPE_H

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
	void (* directive)(ant_t *);
	long long int position[];

};

struct ant_cell_t
{

	//TODO Same as ant_t: C99 VLA? 
	long long int * position;
	void (* rule)(ant_cell_t *, ant_t *); //TODO change to int for error checking
	int state;

};

struct ant_grid_t
{

	ant_t * ants;
	ant_cell_t * origin;
	ant_cell_t * scan_list;

};

ant_t * create_ant(size_t);

ant_t * zero_ant_position(ant_t *, size_t);

ant_grid_t new_grid(ant_cell_t * origin);

ant_cell_t new_cell_empty();

#endif