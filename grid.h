#pragma once
#include <cstdint>
#include <vector>

#include "Ant.h"
#include "cell.h"

// We will be converting what was in the include/grid.h file to an object oriented design

// abstract Grid class
class grid
{
public:
    virtual ~grid() = default;

    // method with a similar signature to grid_getfn
    virtual cell * get_cell(int64_t x, int64_t y) = 0;

    // scan-list to keep track of the active ants in the grid
    // TODO this should be an implementation detail of the grid
    std::vector<ant*> scan_list;

    // get value from cell
    void * get_value(int64_t x, int64_t y)
    {
        cell * cell = get_cell(x, y);
        if (cell)
            return cell->value;
        return nullptr;
    }
    

    // method with a similar signature to grid_insertfn
    virtual cell * insert(int64_t x, int64_t y, void * val) = 0;

    void add_ant(ant& ant)
    {
        // add ant to scan-list
        scan_list.push_back(&ant);
    }

    void tick()
    {
        // iterate through scan-list
        // TODO use polymorphic selector instead of scan-list
        for (auto& ant : scan_list)
        {
            // get cell at ant position
            cell * cell = get_cell(ant->position[0], ant->position[1]);
            if (!cell)
            {
                cell = insert(ant->position[0], ant->position[1], nullptr);
            }
            // call ant directive
            ant->directive(*cell);
        }
    }
    
};
