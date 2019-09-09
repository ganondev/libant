#include <quadtree.h>
#include <standards.h>
#include <stdio.h>

int main()
{

	qt_node_t test;
	test.x = test.y = 1;
	
	qt_node_t testt;
	testt.x = 4;
	testt.y = 0;

	printf("%d", qt_node_compare(&test, &testt));

}
