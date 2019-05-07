#include <stdio.h>
#include "anttype.h"

void printlnd(int i)
{
	
	printf("%d\n", i);
	
}

int main() {

	ant_orientation_t orientation = generate_orientation(5, 6);
	printlnd(orientation.x);

}