﻿#pragma once

#include "la_ant.h"
#include "..\la_automaton.h"

class ant_automaton : public la_automaton
{

    // scan-list to keep track of the active ants in the grid
    std::vector<std::unique_ptr<la_ant>> scan_list;

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
            // get cell at ant position
            auto opt_cell = space_->get_cell(x, y);

            // If the cell does not exist, insert one
            if (!opt_cell.has_value()) {
                la_cell& new_cell = space_->insert(x, y, 0);
                opt_cell = {new_cell};
            }

            // At this point, opt_cell should have a value.
            la_cell& actual_cell = opt_cell.value().get();
            const int old_value = actual_cell.value;
            ant->directive(actual_cell);  // call ant directive
            diffs.push_back({x, y, old_value, actual_cell.value});
        }
        return diffs;
    }
    
public:

    ant_automaton(la_spatial_structure * space) : la_automaton(space) {}

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
