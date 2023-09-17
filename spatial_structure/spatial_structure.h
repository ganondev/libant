#pragma once
#include "cell.h"

struct coords
{
    int64_t x;
    int64_t y;
};

class spatial_structure
{
    coords bounds_;
protected:
    virtual cell * get_cell_impl(coords coords) = 0;
    virtual cell * insert_impl(coords coords, int val) = 0;
public:

    spatial_structure(const coords bounds={}) : bounds_(bounds) {}
    
    virtual ~spatial_structure() = default;

    [[nodiscard]] 
    auto project(const int64_t in_x, const int64_t in_y) const
    {
        const coords s {
            bounds_.x == 0 ? in_x : ((in_x % bounds_.x) + bounds_.x) % bounds_.x,
            bounds_.y == 0 ? in_y : ((in_y % bounds_.y) + bounds_.y) % bounds_.y,
        };
        return s;
    }

    cell * get_cell(const int64_t x, const int64_t y)
    {
        return get_cell_impl(project(x, y));
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
        return insert_impl(project(x, y), val);
    }
};
