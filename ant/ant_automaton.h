#pragma once

#include "../automaton.h"

class ant_automaton : public automaton
{

    // scan-list to keep track of the active ants in the grid
    std::vector<ant*> scan_list;
    
public:

    ant_automaton(spatial_structure * space) : automaton(space) {}
    
    void add_ant(ant& ant)
    {
        // add ant to scan-list
        scan_list.push_back(&ant);
    }

    void tick() override
    {
        // iterate through scan-list
        // TODO use polymorphic selector instead of scan-list
        for (auto& ant : scan_list)
        {
            // get cell at ant position
            cell * cell = space_->get_cell(ant->position[0], ant->position[1]);
            if (!cell)
            {
                cell = space_->insert(ant->position[0], ant->position[1], nullptr);
            }
            // call ant directive
            ant->directive(*cell);
        }
    }
    
};
