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
	qt_node_t ** children;
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
	node->value = value;
	
	return node;

}

static inline qt_node_t * qt_node_get_child(qt_node_t * parent, qt_node_comparison_result_t quadrant)
{

	#ifdef TREEBUG
	printf("Get quadrant: %d\n", quadrant);
	if (parent->is_leaf) printf("Attempted to get child at %d from leaf node at (%lld, %lld)!\n", quadrant, parent->x, parent->y);
	if (quadrant == EQ) printf("qt_node_get_child passed quadrant -1 for parent node at (%lld, %lld).\n", parent->x, parent->y);
	#endif
	return parent->children[quadrant];

}

static inline qt_node_comparison_result_t qt_node_point_compare(qt_node_t * reference, INT x, INT y)
{

	#ifdef TREEBUG
	printf("Comparing point (%lld, %lld) to reference node at (%lld, %lld).\n", x, y, reference->x, reference->y);
	#endif

	if (reference->y == y && reference->x == x) return EQ;
	
	bool vertical = reference->y > y;
	bool horizontal = reference->x > x;

	#ifdef TREEBUG
	printf("Comparison result: %d\n", (vertical * 2) | horizontal);
	#endif

	return (vertical * 2) | horizontal;

}

static inline qt_node_comparison_result_t qt_node_compare(qt_node_t * reference, qt_node_t * target)
{

	#ifdef TREEBUG
	printf("Comparing node at (%lld, %lld) to reference node at (%lld, %lld).\n", target->x, target->y, reference->x, reference->y);
	#endif

	return qt_node_point_compare(reference, target->x, target->y);

}

static inline void qt_node_split(qt_node_t * node)
{

	//node->children = malloc(4 * sizeof(qt_node_t *));
	node->children = calloc(4, sizeof(qt_node_t *));
	node->is_leaf = false;

}

static inline void qt_node_put_child(qt_node_t * parent, INT x, INT y, void * value)
{

	#ifdef TREEBUG
	printf("Inserting node into (%lld, %lld).\n", x, y);
	#endif

	qt_node_t * current_parent = parent;
	while (true)
	{

		qt_node_comparison_result_t quadrant = qt_node_point_compare(current_parent, x, y);
		if (quadrant == EQ)
		{
			
			#ifdef TREEBUG
			printf("Replacing existing value at (%lld, %lld).\n", x, y);
			#endif
			void * old_value;
			if (!(old_value = current_parent->value)) free(old_value);
			current_parent->value = value;
			return;

		}
		else if (current_parent->is_leaf)
		{

			#ifdef TREEBUG
			printf("Encountered leaf node at (%lld, %lld). Splitting and inserting at (%lld, %lld).\n", current_parent->x, current_parent->y, x, y);
			#endif
			qt_node_split(current_parent);
			current_parent->children[quadrant] = qt_node_create(x, y, value);
			return;

		}
		else
		{

			#ifdef TREEBUG
			printf("Continuing to dig for insert location for (%lld, %lld) from (%lld, %lld) to quadrant %d.\n", x, y, current_parent->x, current_parent->y, quadrant);
			#endif
			qt_node_t * child_ptr = qt_node_get_child(current_parent, quadrant);
			if (child_ptr == NULL)
			{

				#ifdef TREEBUG
				printf("Terminating insert for (%lld, %lld) to NULL pointer in quadrant %d.\n", x, y, quadrant);
				#endif

				current_parent->children[quadrant] = qt_node_create(x, y, value);
				return;

			}
			current_parent = child_ptr;

		}

	}

}
#endif
