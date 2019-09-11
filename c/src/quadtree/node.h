#ifndef __libant_quadtree_node
#define __libant_quadtree_node

#include <standards.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef TREEBUG
#include <stdio.h>
#endif

typedef struct qt_node_t qt_node_t;

struct qt_node_t
{

	INT x;
	INT y;
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

static inline qt_node_t * qt_node_create(INT x, INT y, void * value)
{

	qt_node_t * node = malloc(sizeof(qt_node_t));
	node->x = x;
	node->y = y;
	node->is_leaf = true;
	
	return node;

}

static inline qt_node_t * qt_node_get_child(qt_node_t * parent, qt_node_comparison_result_t quadrant)
{

	#ifdef TREEBUG
	if (parent->is_leaf) printf("Attempted to get child at %d from leaf node at (%lld, %lld)!\n", quadrant, parent->x, parent->y);
	if (quadrant == EQ) printf("qt_node_get_child passed quadrant -1 for parent node at (%lld, %lld).\n", parent->x, parent->y);
	#endif
	return &parent->children[quadrant];

}

static inline qt_node_comparison_result_t qt_node_point_compare(qt_node_t * reference, INT x, INT y)
{

	#ifdef TREEBUG
	printf("Comparing point (%lld, %lld) to reference node at (%lld, %lld).\n", target->x, target->y, reference->x, reference->y);
	#endif

	if (reference->y == y && reference->x == x) return EQ;
	
	bool vertical = reference->y > target->y;
	bool horizontal = reference->x > target->x;

	return (vertical * 2) | horizontal;

}

static inline qt_node_comparison_result_t qt_node_compare(qt_node_t * reference, qt_node_t * target)
{

	#ifdef TREEBUG
	printf("Comparing node at (%lld, %lld) to reference node at (%lld, %lld).\n", target->x, target->y, reference->x, reference->y);
	#endif

	return qt_node_point_compare(reference, target->x, target->y);

}

static inline void qt_node_put_child(qt_node_t * parent, INT x, INT y, void * value)
{

	qt_node_t * current_parent = parent;
	qt_node_t * current_child = child;
	while (true)
	{

		qt_node_comparison_result_t quadrant = qt_node_compare(current_parent, current_child);
		if (quadrant == EQ)
		{

			current_parent->value = current_child->value;
			return;

		}
		else
		{

			

		}

	}

}
#endif
