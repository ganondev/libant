#include <antalgo.h>

const int NORTH_2D[2] = {0, -1};
const int EAST_2D[2] = {1, 0};
const int SOUTH_2D[2] = {0, 1};
const int WEST_2D[2] = {-1, 0};

const int * CARDINAL_2D[4] = {NORTH_2D, EAST_2D, SOUTH_2D, WEST_2D};

//TODO typedef compatibility
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

// cast-compatible for rulefn tupe
void langtons_ant_default_rule(ant_cell_t * cell, ant_t * ant)
{

	int * value = cell->value;
	*value = !(*value); //TODO this should be a rotation, langton's ant states can have endless enumeration

	ant->orientation = (ant->orientation + (*value ? 1 : -1)) % 4;

}
