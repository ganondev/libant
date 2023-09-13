#include "ant.h"

const int NORTH_2D[2] = {0, -1};
const int EAST_2D[2] = {1, 0};
const int SOUTH_2D[2] = {0, 1};
const int WEST_2D[2] = {-1, 0};

const int * CARDINAL_2D[4] = {NORTH_2D, EAST_2D, SOUTH_2D, WEST_2D};

void langtons_ant::directive(cell& cell)
{
    const auto value = cell.value;
    cell.value = !value;

    orientation = (orientation + (value ? 1 : -1)) % 4;

    position[0] += CARDINAL_2D[orientation][0];
    position[1] += CARDINAL_2D[orientation][1];
}
