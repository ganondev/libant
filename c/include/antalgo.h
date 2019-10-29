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
void next_state_create(ant_grid_t *);

ant_grid_t langtons_ant(/* TODO initial state */);

void langtons_ant_default_directive(ant_t *, ant_grid_t *);

//ant_cell_t langtons_ant_default_generator(INT x, INT y);

ant_t * create_langtons_ant(ant_grid_t *);

#endif
