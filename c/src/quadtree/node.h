#ifndef __libant_quadtree_node
#define __libant_quadtree_node

#include <stdbool.h>
#include <stdlib.h>

#include <standards.h>
#include <cell.h>

#ifdef TREEBUG
#define LIBANT_DEBUG
#include <stdio.h>
#include <antmacro.h>
#endif

typedef struct qt_node_t qt_node_t;

struct qt_node_t
{

	ant_cell_t cell_head;
	INT x;
	INT y;
	bool is_leaf;
	qt_node_t ** children;

};

typedef enum qt_node_comparison_result_t qt_node_comparison_result_t;

enum qt_node_comparison_result_t {

	EQ = -1,
	NE = 0,
	NW = 1,
	SW = 3,
	SE = 2

};

#ifdef TREEBUG
static char * stringify_result(qt_node_comparison_result_t quadrant)
{

	static char * quadrants[] = { "NE", "NW", "SE", "SW" };
	return quadrant == EQ ? "EQ" : quadrants[quadrant];

}
#endif

static inline qt_node_t * qt_node_create(INT x, INT y, void * value) //TODO valueless version?
{

	qt_node_t * node = malloc(sizeof(qt_node_t));
	node->x = x;
	node->y = y;
	node->is_leaf = true;
	node->cell_head.value = value;
	node->cell_head.rule = NULL;
	
	return node;

}

static inline qt_node_t * qt_node_get_child(qt_node_t * parent, qt_node_comparison_result_t quadrant)
{

	#ifdef TREEBUG
	printf("Get quadrant: %d\n", quadrant);
	if (parent->is_leaf) printf(ERROR("Attempted to get child at %d from leaf node at (%lld, %lld)!\n"), quadrant, parent->x, parent->y);
	if (quadrant == EQ) printf(ERROR("qt_node_get_child passed quadrant -1 for parent node at (%lld, %lld).\n"), parent->x, parent->y);
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
			if (!(old_value = current_parent->cell_head.value)) free(old_value);
			current_parent->cell_head.value = value;
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

static inline qt_node_t * qt_node_find(qt_node_t * root, INT x, INT y)
{

	#ifdef TREEBUG
	printf(TRACE("Searching for node at (%lld, %lld).\n"), x, y);
	#endif

	qt_node_comparison_result_t quadrant = qt_node_point_compare(root, x, y);
	if (quadrant == EQ)
	{
		
		#ifdef TREEBUG
		puts(DEBUG("Target is root"));
		#endif
		return root;

	}
	else
	{

		#ifdef TREEBUG
		printf(DEBUG("Going from (%lld, %lld)...\n"), root->x, root->y);
		#endif

		qt_node_t * current_parent = root;
		while (true)
		{

			if (current_parent->is_leaf)
			{

				#ifdef TREEBUG
				printf(DEBUG("\tDead end :( -- Leaf node at %s child.\n"), stringify_result(quadrant));
				#endif
				return NULL;
			
			}
			else
			{

				current_parent = qt_node_get_child(current_parent, quadrant);
				if (current_parent == NULL)
				{
					#ifdef TREEBUG
					printf(DEBUG("\tDead end :( -- NULL node at %s child.\n"), stringify_result(quadrant));
					#endif
					return NULL;
				
				}

				#ifdef TREEBUG
				printf(DEBUG("\tto %s child at (%lld, %lld)...\n"), stringify_result(quadrant), current_parent->x, current_parent->y);
				#endif
				quadrant = qt_node_point_compare(current_parent, x, y);
				if (quadrant == EQ)
				{
					
					#ifdef TREEBUG
					puts(DEBUG("\tfound it :)"));
					#endif
					return current_parent;

				}

			}

		}

	}

}
#endif
