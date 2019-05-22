#ifndef LIBANT_ANTALGO_H
#define LIBANT_ANTALGO_H

#include "anttype.h"

static const int NORTH_2D[2] = {0, -1};
static const int SOUTH_2D[2] = {0, 1};
static const int WEST_2D[2]= {-1, 0};
static const int EAST_2D[2]= {1, 0};

// general functions for this library's automaton
void turmite_update(ant_t * ant);
void next_state_create(ant_grid_t * grid);

ant_grid_t langtons_ant(/* TODO initial state */);

#endif