#include "ant.h"

void langtons_ant::directive(cell& cell)
{
    const auto value = static_cast<bool>(cell.value);
    cell.value = static_cast<void*>(reinterpret_cast<bool*>(!value));

    orientation = (orientation + (value ? 1 : -1)) % 4;

    position[0] += CARDINAL_2D[orientation][0];
    position[1] += CARDINAL_2D[orientation][1];
}
