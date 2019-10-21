#ifndef LIBANT_CELL_H
#define LIBANT_CELL_H

#include "standards.h"

typedef struct ant_cell_t ant_cell_t;

struct ant_cell_t // TODO merge with data structure cells
{

	void (* rule)(ant_cell_t *, ant_t *);
	int state;
	void * value; //TODO consider if state is needed

};

#endif
