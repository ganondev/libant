#pragma once

#include "../automaton.h"

class ant_automaton : public automaton
{

    // scan-list to keep track of the active ants in the grid
    std::vector<std::unique_ptr<ant>> scan_list;

    std::vector<positional_diff> do_tick() override
    {
        std::vector<positional_diff> diffs;
        // iterate through scan-list
        // TODO use polymorphic selector instead of scan-list
        for (const auto& ant : scan_list)
        {
            // TODO it shouldn't be the responsibility of the automaton to
            // project the ant's position - needs to be handled by the spatial structure
            const auto [x, y] = space_->project(ant->position[0], ant->position[1]);
            int old_value;
            // get cell at ant position
            cell * cell = space_->get_cell(x, y);
            if (!cell)
            {
                cell = space_->insert(x, y, 0);
                old_value = 0;
            }
            else
            {
                old_value = cell->value;
            }
            // call ant directive
            ant->directive(*cell);
            diffs.push_back({x, y, old_value, cell->value});
        }
        return diffs;
    }
    
public:

    ant_automaton(spatial_structure * space) : automaton(space) {}

    // Creates an instance of the ant for tracking by the automaton and returns
    // a raw non-owning pointer to the ant.
    template<typename T>
    T* add_ant()
    {
        auto ptr = std::make_unique<T>();
        T* rawPtr = ptr.get();
        // add ant to scan-list
        scan_list.push_back(std::move(ptr));
        return rawPtr;
    }
    
};
