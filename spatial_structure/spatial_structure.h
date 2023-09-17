#pragma once
#include "cell.h"

struct coords
{
    int64_t x;
    int64_t y;
};

struct bounds
{
    int x;
    int y;

    [[nodiscard]] 
    auto project(const int64_t in_x, const int64_t in_y) const
    {
        const coords s {
            x == 0 ? in_x : in_x % x,
            y == 0 ? in_y : in_y % y,
        };
        return s;
    }
};

class spatial_structure
{
    bounds bounds_;
protected:
    virtual cell * get_cell_impl(coords coords) = 0;
    virtual cell * insert_impl(coords coords, int val) = 0;
public:

    spatial_structure(const bounds bounds={}) : bounds_(bounds) {}
    
    virtual ~spatial_structure() = default;

    cell * get_cell(const int64_t x, const int64_t y)
    {
        return get_cell_impl(bounds_.project(x, y));
    }

    // get value from cell
    int get_value(const int64_t x, const int64_t y)
    {
        if (const cell * cell = get_cell(x, y))
            return cell->value;
        return 0;
    }
    

    // method with a similar signature to grid_insertfn
    cell * insert(const int64_t x, const int64_t y, const int val)
    {
        return insert_impl(bounds_.project(x, y), val);
    }
};
