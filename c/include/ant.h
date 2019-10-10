#ifndef LIBANT_ANT_H
#define LIBANT_ANT_H

#include "standards.h"
#include <string.h> // for memset
#include <stdlib.h>

typedef struct ant_t ant_t;

// represents abstractly an 'active' or 'living' cell in a cellular automaton
struct ant_t
{

	unsigned int orientation;
	size_t tuple_size;
	void (* directive)(ant_t *, ...);
	INT position[];

};

inline ant_t * resize_ant_position(ant_t * ant, size_t size)
{

	ant = realloc(ant, sizeof(ant_t) + size * sizeof(INT));
	ant->tuple_size = size;

	return ant;

}

inline void zero_ant_position(ant_t * ant)
{

	memset(ant->position, 0, ant->tuple_size * sizeof(INT));

}

inline ant_t * create_ant(size_t position_size)
{

	ant_t * ant = resize_ant_position(NULL, position_size);
	zero_ant_position(ant);
	ant->directive = NULL;
	ant->orientation = 0;
	return ant;

}

#endif
