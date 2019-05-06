#include <stdlib.h>

#define INTSIZE sizeof(int)

//variable sized integer array
typedef int * position_t;

//Two degrees of expressability, generally rotation for 3 dimensional motion
typedef struct orientation_t {
	
	int x;
	int y;
	
} orientation_t;

//Should represent a single ant on 2D or 3D tape
typedef struct turmite_t {
	
	position_t position;
	orientation_t orientation;
	
} turmite_t;

position_t buildPosition(size_t size)
{
	
	return malloc(-1);
	
}