#ifndef LIBANT_ANTALGO_H
#define LIBANT_ANTALGO_H

#include "ant.h"
#include "grid.h"

const int NORTH_2D[2];
const int EAST_2D[2];
const int SOUTH_2D[2];
const int WEST_2D[2];

const int * CARDINAL_2D[4];

// general functions for this library's automaton
void turmite_update(ant_t * ant);
void next_state_create(ant_grid_t * grid);

ant_grid_t langtons_ant(/* TODO initial state */);

void langtons_ant_default_directive(ant_t *, ...);

ant_t * create_langtons_ant(void);

#endif
