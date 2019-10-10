#ifndef LIBANT_CELL_H
#define LIBANT_CELL_H

#include "standards.h"

typedef struct ant_cell_t ant_cell_t;

struct ant_cell_t // TODO merge with data structure cells
{

	// TODO same as ant_t: c99 VLA?
	INT * position;
	void (* rule)(ant_cell_t *, ant_t *);
	int state;

};

#endif
