#ifndef LIBANT_CELL_H
#define LIBANT_CELL_H

#include "standards.h"
#include "ant.h"

typedef struct ant_cell_t ant_cell_t;

typedef void (* rulefn)(ant_cell_t *, ...);

struct ant_cell_t // TODO merge with data structure cells
{

	rulefn rule;
	int state;
	void * value; //TODO consider if state is needed

};

#endif
