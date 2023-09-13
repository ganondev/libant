#pragma once
#include "cell.h"

class spatial_structure
{
public:
    virtual ~spatial_structure() = default;
    // method with a similar signature to grid_getfn
    virtual cell * get_cell(int64_t x, int64_t y) = 0;

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
};
