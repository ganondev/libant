#include "antalgo.h"

void next_state_create(grid_t * grid)
{

    int ant_count = sizeof(grid->turmites);
    for (int i = 0; i < ant_count; i++)
    {

        turmite_t * ant = grid->turmites[i];
        cell_t * ant_cell = ant->position;
        ant_cell->rule(ant_cell, ant);

    }

}