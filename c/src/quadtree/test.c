#include <node.h>
#include <standards.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

const char * quadrants[] = { "NE", "NW", "SW", "SE" };

int check_node(qt_node_t * root, qt_node_comparison_result_t * path, size_t path_size, INT x, INT y, bool is_leaf)
{
	
	printf("\nSearching for (%lld, %lld). Starting at node (%lld, %lld)\n", x, y, root->x, root->y);
	
	for (size_t i = 0; i < path_size; i++)
	{
		
		root = root->children[path[i]];
		printf("\tto quadrant %s for node at (%lld, %lld)\n", quadrants[path[i]], root->x, root->y);
		
	}
	
	printf("Reached expected node at (%lld, %lld) - is_leaf: %d\n\n", root->x, root->y, root->is_leaf);
	
	assert(root != NULL);
	assert(x != -1 && root->x == x);
	assert(y != -1 && root->y == y);
	assert(root->is_leaf == is_leaf);
	
}

int test1()
{
	qt_node_t test;
	test.x = test.y = 1;
	
	qt_node_t testt;
	testt.x = 4;
	testt.y = 0;

	printf("%d\n", qt_node_compare(&test, &testt));

	qt_node_t * node = qt_node_create(80, 9, NULL);

	printf("%lld %lld\n", node->x, node->y);
	
	qt_node_t * other = qt_node_create(80, 9, NULL);

	printf("%lld %lld\n", node->x, node->y);

	printf("%d\n", qt_node_compare(node, other));

	printf("other is leaf: %d\n", other->is_leaf);
	qt_node_split(other);
	printf("other is leaf: %d\n", other->is_leaf);

	other->children[0] = qt_node_create(100, 100, NULL);
	
	qt_node_t * child = qt_node_get_child(other, NE);

	printf("child (%lld, %lld) is leaf: %d\n", child->x, child->y, child->is_leaf);
	qt_node_put_child(child, 9, 9, NULL);
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

}

typedef qt_node_comparison_result_t qdrnt;

//deep put_child tests
int test2()
{
	
	qt_node_t * test = qt_node_create(0, 0, NULL);
	qt_node_put_child(test, 1, 1, NULL);
	check_node(test, (qdrnt[]){NE}, 1, 1, 1, true);
	qt_node_put_child(test, 2, 2, NULL);
	check_node(test, (qdrnt[]){NE}, 1, 1, 1, false);
	check_node(test, (qdrnt[]){NE, NE}, 2, 2, 2, true);
	qt_node_put_child(test, -6, 8, NULL); //SEGFAULT in qt_node_point_compare()
	check_node(test, (qdrnt[]){NW}, 1, -6, 8, true);
	
}

int main()
{
	
	test1();
	test2();

}
