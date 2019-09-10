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

}
