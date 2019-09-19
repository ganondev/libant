#include <node.h>
#include <standards.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

int main()
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

	printf("child (%lld, %lld)\n", child->x, child->y);	

}
