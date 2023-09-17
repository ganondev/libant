#pragma once

#include "../automaton.h"

class ant_automaton : public automaton
{

    // scan-list to keep track of the active ants in the grid
    std::vector<std::unique_ptr<ant>> scan_list;
    
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
                cell = space_->insert(ant->position[0], ant->position[1], 0);
            }
            // call ant directive
            ant->directive(*cell);
        }
    }
    
};
