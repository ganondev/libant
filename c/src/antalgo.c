#include "antalgo.h"

const int NORTH_2D[2] = {0, -1};
const int EAST_2D[2] = {1, 0};
const int SOUTH_2D[2] = {0, 1};
const int WEST_2D[2] = {-1, 0};

const int * CARDINAL_2D[4] = {NORTH_2D, EAST_2D, SOUTH_2D, WEST_2D};

void langtons_ant_default_directive(ant_t * ant, ...)
{
	
	ant->position[0] += CARDINAL_2D[ant->orientation][0];
	ant->position[1] += CARDINAL_2D[ant->orientation][1];
	
}

ant_t * create_langtons_ant(void)
{
	
	ant_t * ant = create_ant(2);
	ant->directive = langtons_ant_default_directive;
	return ant;
	
}