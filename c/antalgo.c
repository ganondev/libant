#include "antalgo.h"

// void next_state_create(grid_t * grid)
// {

    // int ant_count = sizeof(grid->turmites);
    // for (int i = 0; i < ant_count; i++)
    // {

        // turmite_t * ant = grid->turmites[i];
        // cell_t * ant_cell = ant->position;
        // ant_cell->rule(ant_cell, ant);

    // }

// }

void langtons_ant_default_directive(ant_t * ant)
{
	
	ant->position[0] += CARDINAL_2D[ant->orientation][0];
	ant->position[1] += CARDINAL_2D[ant->orientation][1];
	
}

ant_t * create_langtons_ant()
{
	
	ant_t * ant = create_ant(2);
	ant->directive = langtons_ant_default_directive;
	return ant;
	
}