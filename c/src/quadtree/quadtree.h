#ifndef __libant_quadtree
#define __libant_quadtree

#ifdef TREEBUG
#include <stdio.h>
#define LIBANT_DEBUG
#endif

#include <standards.h>
#include <antmacro.h>

#include <node.h>

#include <stdlib.h>
#include <stdbool.h>

typedef struct libant_quadtree_t libant_quadtree_t;

struct libant_quadtree_t
{

	qt_node_t * root;
	//TODO what else to do with this

};

libant_quadtree_t * libant_quadtree_create();

void qt_insert(libant_quadtree_t *, INT, INT, void *);

qt_node_t * qt_get(libant_quadtree_t *, INT, INT);

#endif
