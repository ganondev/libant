#pragma once
#include "la_scanning_automaton.h"
#include "../la_automaton.h"

class la_game_of_life final : public la_scanning_automaton
{
    static int game_of_life_mapper(const int64_t x, const int64_t y, const la_cell& cell, la_spatial_structure * space)
    {
        const int64_t num_neighbors = space->get_num_neighbors(x, y);
        if (cell.value == 0 && num_neighbors == 3)
        {
            return 1;
        }
        if (cell.value == 1 && (num_neighbors < 2 || num_neighbors > 3))
        {
            return 0;
        }
        return cell.value;
    }
public:
    la_game_of_life(la_spatial_structure * space) : la_scanning_automaton(space, game_of_life_mapper) {}

    void toggle_cell(const int64_t x, const int64_t y) const
    {
        const auto my_cell = space_->get_cell(x, y);
        if (my_cell.has_value())
        {
            auto& cell = my_cell->get();
            cell.value = !cell.value;
        }
        else
        {
            space_->insert(x, y, 1);
        }
    }
};
