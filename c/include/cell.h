#ifndef LIBANT_CELL_H
#define LIBANT_CELL_H

#include "standards.h"

typedef struct ant_cell_t ant_cell_t;

typedef void (* cell_rulefn)(ant_cell_t *, ...);
typedef ant_cell_t * (* grid_generatorfn)(); // TODO Might not need this

struct ant_cell_t
{

	cell_rulefn rule;
	int state; //TODO consider if state is needed
	void * value; 

};

#endif
