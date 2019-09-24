#include <node.h>
#include <standards.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

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

int main()
{
	
	test1();

}
