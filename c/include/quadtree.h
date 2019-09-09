#ifndef __libant_quadtree_node
#define __libant_quadtree_node

typedef struct qt_node_t qt_node_t;

struct qt_node_t
{

	INT x;
	INT y;
	UINT visits;
	void * value;	

}

#endif
