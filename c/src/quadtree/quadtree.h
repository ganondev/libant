#ifndef __libant_quadtree
#define __libant_quadtree

#ifdef TREEBUG
#include <stdio.h>
#define LIBANT_DEBUG
#endif

#include <stdlib.h>
#include <stdbool.h>

#include <standards.h>
#include <antmacro.h>
#include <grid.h>

#include "node.h"


typedef struct libant_quadtree_t libant_quadtree_t;

struct libant_quadtree_t
{

	ant_grid_t grid_head;
	qt_node_t * root;
	//TODO what else to do with this

};

void libant_quadtree_create(libant_quadtree_t *);

void qt_insert(libant_quadtree_t *, INT, INT, void *, cell_rulefn);

qt_node_t * qt_get(libant_quadtree_t *, INT, INT);

#endif
