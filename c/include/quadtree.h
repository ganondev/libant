#ifndef __libant_quadtree_node
#define __libant_quadtree_node

#include <standards.h>
#include <stdbool.h>
#ifdef TREEBUG
#include <stdio.h>
#endif

typedef struct qt_node_t qt_node_t;

struct qt_node_t
{

	INT x;
	INT y;
	UINT visits;
	bool is_leaf;
	qt_node_t * children;
	void * value;	

};

typedef enum qt_node_comparison_result_t qt_node_comparison_result_t;

enum qt_node_comparison_result_t {

	EQ = -1,
	NE = 0,
	NW = 1,
	SW = 3,
	SE = 2

};

qt_node_comparison_result_t qt_node_compare(qt_node_t * reference, qt_node_t * target)
{

	#ifdef TREEBUG
	printf("Comparing node at (%lld, %lld) to reference node at (%lld, %lld).", target->x, target->y, reference->x, reference->y);
	#endif
	if (reference->y == target->y && reference->x == target->x) return EQ;
	
	bool vertical = reference->y > target->y;
	bool horizontal = reference->x > target->x;

	return (vertical * 2) | horizontal;

}

#endif
