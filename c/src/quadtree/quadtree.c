#include "quadtree.h"

libant_quadtree_t * libant_quadtree_create() //TODO might what to configure this a bit
{

	#ifdef TREEBUG
	puts(TRACE("Creating new quadtree."));
	#endif
	libant_quadtree_t *  tree = malloc(sizeof(libant_quadtree_t));
	tree->root = qt_node_create(0, 0, NULL);
	return tree;

}

void qt_insert(libant_quadtree_t * tree, INT x, INT y, void * value)
{

	#ifdef TREEBUG
	printf(TRACE("Inserting into tree @ (%lld, %lld).\n"), x, y);
	#endif
	qt_node_put_child(tree->root, x, y, value);

}

qt_node_t * qt_get(libant_quadtree_t * tree, INT x, INT y)
{

	qt_node_find(tree->root, x, y);

}
