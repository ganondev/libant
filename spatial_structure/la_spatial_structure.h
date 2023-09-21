#pragma once
#include <optional>

#include "la_cell.h"

struct coords
{
    int64_t x;
    int64_t y;
};

class la_spatial_structure
{

    using opt_cell = std::optional<std::reference_wrapper<la_cell>>;
    
    coords bounds_;
protected:
    virtual opt_cell get_cell_impl(coords coords) = 0;
    virtual la_cell& insert_impl(coords coords, int val) = 0;
public:

    la_spatial_structure(const coords bounds={}) : bounds_(bounds) {}
    
    virtual ~la_spatial_structure() = default;

    [[nodiscard]] 
    auto project(const int64_t in_x, const int64_t in_y) const
    {
        const coords s {
            bounds_.x == 0 ? in_x : ((in_x % bounds_.x) + bounds_.x) % bounds_.x,
            bounds_.y == 0 ? in_y : ((in_y % bounds_.y) + bounds_.y) % bounds_.y,
        };
        return s;
    }

    opt_cell get_cell(const int64_t x, const int64_t y)
    {
        return get_cell_impl(project(x, y));
    }

    // get value from cell
    [[nodiscard]]
    int get_value(const int64_t x, const int64_t y)
    {
        if (const auto opt_cell = get_cell(x, y); opt_cell)
            return opt_cell->get().value;
        return 0;
    }
    
    // method with a similar signature to grid_insertfn
    la_cell& insert(const int64_t x, const int64_t y, const int val)
    {
        return insert_impl(project(x, y), val);
    }
};
