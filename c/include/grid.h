#ifndef LIBANT_GRID_H
#define LIBANT_GRID_H

#include <quadtree/quadtree.h>
#include "standards.h"
#include "ant.h"
#include "cell.h"

typedef struct ant_grid_t ant_grid_t;

struct ant_grid_t // eventually other data structures should be inlined castable extensions of this
{

	//TODO void * (* get)(INT x, INT y);
	//TODO void (* insert)(INT x, INT y, void * value);

	ant_t ** ants;
	ant_cell_t ** scan_list;

	libant_quadtree_t * tree; // TODO will need to be heavily generalized
	// TODO ^ perhaps the generalization should occur here and this member should be a value instead of a pointer
};

inline void * grid_get(ant_grid_t * grid, INT x, INT y) //TODO should probably be an int
{

	qt_node_t * node = qt_get(grid->tree, x, y);
	if (node) return node->value;
	else
	{

		#ifdef TREEBUG
		puts(DEBUG("Node is NULL (none was found). Returning NULL value"));
		#endif
		return NULL;

	}

}

inline void grid_insert(ant_grid_t * grid, INT x, INT y, void * value)
{

	qt_insert(grid->tree, x, y, value);

}

ant_grid_t * new_grid(/*ant_cell_t * origin*/); //TODO bring it back but make it generic

#endif
