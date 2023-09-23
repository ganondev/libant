#pragma once
#include "la_automaton.h"

class la_game_of_life : public la_automaton
{
protected:
    std::vector<positional_diff> do_tick() override
    {
        auto space_copy = space_->clone();
        std::vector<positional_diff> diffs;
        for (auto [x, y, opt_cell] : *space_)
        {
            la_cell& my_cell = opt_cell.has_value() ? opt_cell.value().get() : space_->insert(x, y, 0);
            int64_t old_value = my_cell.value;
            int64_t num_neighbors = space_copy->get_num_neighbors(x, y);
            if (old_value == 0 && num_neighbors == 3)
            {
                my_cell.value = 1;
            }
            else if (old_value == 1 && (num_neighbors < 2 || num_neighbors > 3))
            {
                my_cell.value = 0;
            }
            if (old_value != my_cell.value)
            {
                diffs.push_back({x, y, old_value, my_cell.value});
            }
        }
        return diffs;
    }
public:
    la_game_of_life(la_spatial_structure * space) : la_automaton(space) {}

    void toggle_cell(int64_t x, int64_t y)
    {
        auto my_cell = space_->get_cell(x, y);
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
