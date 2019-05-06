#include <stdio.h>
#include <anttype.h>

void printlnd(int i)
{
	
	printf("%d\n", i);
	
}

int main() {
	
	position_t pos = buildPosition(0);
	pos[0] = 0;
	pos[1] = 2;
	pos[2] = 19233;
	
	orientation_t or;
	or.x = 0;
	or.y = 0;
	
	turmite_t ant;
	ant.position = pos;
	ant.orientation = or;
	
	printlnd(pos[2]);
	
}