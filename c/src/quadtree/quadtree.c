#include "quadtree.h"

void libant_quadtree_create(libant_quadtree_t * grid) //TODO may need to pass root cell rule here
{
	
	#ifdef TREEBUG
	puts(TRACE("Creating new quadtree."));
	#endif
	new_grid((ant_grid_t *)grid, (grid_getfn)qt_get, (grid_insertfn)qt_insert);
	grid->root = qt_node_create(0, 0, NULL, NULL); //cell rule replaces last NULL

}

void qt_insert(libant_quadtree_t * tree, INT x, INT y, void * value, cell_rulefn rule)
{

	#ifdef TREEBUG
	printf(TRACE("Inserting into tree @ (%lld, %lld).\n"), x, y);
	#endif
	qt_node_put_child(tree->root, x, y, value, rule);

}

qt_node_t * qt_get(libant_quadtree_t * tree, INT x, INT y)
{

	return qt_node_find(tree->root, x, y);

}
