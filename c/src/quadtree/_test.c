#define LIBANT_DEBUG

#include "quadtree.h"
#include "node.h"
#include <grid.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define t(a) assert( a )

#ifndef _WIN32
#include <mcheck.h>

void no_op(enum mcheck_status status) { }

void probe(qt_node_t * node)
{

	printf(DEBUG("Probing node @ (%lld, %lld)...\n"), node->x, node->y);
	printf("\tmprobe result: %d\n", mprobe(node));

}

#define mprobe_assert(val) assert( mprobe( val ) == MCHECK_OK )

#define probe(node) probe(node)

#else

#define mprobe_assert(val)
#define probe(node)

#endif

const char * quadrants[] = { "NE", "NW", "SE", "SW" };

qt_node_t * check_node(qt_node_t * root, qt_node_comparison_result_t * path, size_t path_size, INT x, INT y, bool is_leaf)
{
	
	printf("\nSearching for (%lld, %lld). Starting at node (%lld, %lld)\n", x, y, root->x, root->y);
	
	for (size_t i = 0; i < path_size; i++)
	{
		
		root = root->children[path[i]];
		printf("\tto quadrant %s for node at (%lld, %lld)\n", quadrants[path[i]], root->x, root->y);
		
	}
	
	printf("\tReached expected node at (%lld, %lld) - is_leaf: %d\n\n", root->x, root->y, root->is_leaf);
	
	assert(root != NULL);
	assert(root->x == x);
	assert(root->y == y);
	assert(root->is_leaf == is_leaf);

	return root;
	
}

int test1()
{

	puts(TRACE("Starting test 1."));

	qt_node_t test;
	test.x = test.y = 1;
	
	qt_node_t testt;
	testt.x = 4;
	testt.y = 0;

	printf("%d\n", qt_node_compare(&test, &testt));

	qt_node_t * node = qt_node_create(80, 9, NULL, NULL);

	printf("%lld %lld\n", node->x, node->y);
	
	qt_node_t * other = qt_node_create(80, 9, NULL, NULL);

	printf("%lld %lld\n", node->x, node->y);

	printf("%d\n", qt_node_compare(node, other));

	printf("other is leaf: %d\n", other->is_leaf);
	qt_node_split(other);
	printf("other is leaf: %d\n", other->is_leaf);

	other->children[0] = qt_node_create(100, 100, NULL, NULL);
	
	qt_node_t * child = qt_node_get_child(other, NE);

	printf("child (%lld, %lld) is leaf: %d\n", child->x, child->y, child->is_leaf);
	qt_node_put_child(child, 9, 9, NULL, NULL);
	printf("child (%lld, %lld) is leaf: %d\n", child->x, child->y, child->is_leaf);
	qt_node_t * q = child->children[3];
	puts("1");
	INT a = q->x;
	puts("2");
	INT b = q->y;
	puts("3");
	int c = q->is_leaf;
	puts("4");
	printf("child (%lld, %lld) is leaf: %d\n", child->children[3]->x, child->children[3]->y, child->children[3]->is_leaf);

	puts(IO_OK("Passed test 1!"));

	return 1;

}

typedef qt_node_comparison_result_t qdrnt;


//deep put_child tests
int test2()
{

	puts(TRACE("Starting test 2."));
	
	qt_node_t * test = qt_node_create(0, 0, NULL, NULL);
	qt_node_put_child(test, 1, 1, NULL, NULL);
	check_node(test, (qdrnt[]){NE}, 1, 1, 1, true);
	qt_node_put_child(test, 2, 2, NULL, NULL);
	check_node(test, (qdrnt[]){NE}, 1, 1, 1, false);
	check_node(test, (qdrnt[]){NE, NE}, 2, 2, 2, true);
	qt_node_put_child(test, -6, 8, NULL, NULL);
	check_node(test, (qdrnt[]){NW}, 1, -6, 8, true);
	qt_node_put_child(test, -2, -1, NULL, NULL);
	check_node(test, (qdrnt[]){SW}, 1, -2, -1, true);
	qt_node_put_child(test, 5, -6, NULL, NULL);
	check_node(test, (qdrnt[]){SE}, 1, 5, -6, true);

	qt_node_put_child(test, 2, -1, NULL, NULL);
	check_node(test, (qdrnt[]){SE, NW}, 2, 2, -1, true);
	//check that replacement works correctly
	qt_node_put_child(test, 2, -1, NULL, NULL);
	qt_node_t * cnode = check_node(test, (qdrnt[]){SE, NW}, 2, 2, -1, true);
	//check that replacement actually inserts value
	qt_node_put_child(test, 2, -1, malloc(1), NULL);
	void * value = cnode->cell_head.value;
	mprobe_assert(value);

	//do search tests
	assert(qt_node_find(test, 0, 0) == test);
	assert(qt_node_find(test, 2, -1) == cnode);
	assert(qt_node_find(test, 100, 100) == NULL);

	puts(IO_OK("Passed test 2!"));

	return 1;

}

//test the quadtree structure
int test3()
{

	puts(TRACE("Starting test 3."));

	libant_quadtree_t * tree = libant_quadtree_create();
	qt_insert(tree, 0, 0, malloc(1), NULL);
	probe(tree->root);
	qt_insert(tree, 1, 1, malloc(500), NULL);
	qt_insert(tree, 5, 5, NULL, NULL);
	probe(tree->root->children[0]);

	assert(qt_get(tree, 0, 0) == tree->root); // root comparison works
	assert(qt_get(tree, 1, 1) == tree->root->children[0]); // child find works
	probe(qt_get(tree, 5, 5)); // iterative child find works
	assert(qt_get(tree, -1, -1) == NULL); // doesn't exist - null node
	assert(qt_get(tree, 3, 3) == NULL); // doesn't exist - parent is leaf

	puts(IO_OK("Passed test 3!"));

	return 1;

}

int main()
{

	puts(TRACE("\nBeginning quadtree tests.\n"));
	
	test1();
	puts("");
	test2();
	puts("");
	test3();

	puts(IO_OK("\nQuadtree tests complete!\n"));

}
