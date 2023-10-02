#pragma once
#include <vector>
#include "../spatial_structure/la_spatial_structure.h"

// We will be converting what was in the include/grid.h file to an object oriented design

struct positional_diff
{
    int64_t x;
    int64_t y;
    int64_t old_value;
    int64_t new_value;
};


class la_automaton
{
protected:
    la_spatial_structure * space_;
    int iteration_ = 0;

    virtual std::vector<positional_diff> do_tick() = 0;
public:
    
    la_automaton(la_spatial_structure * space) : space_(space) {}
    
    virtual ~la_automaton() = default;
    
    std::vector<positional_diff> tick()
    {
        iteration_++;
        return do_tick();
    }

    [[nodiscard]]
    int get_value(int64_t x, int64_t y) const
    {
        return space_->get_value(x, y);
    }

    void set_value(int64_t x, int64_t y, const int val)
    {
        space_->insert(x, y, val);
    }

    [[nodiscard]]
    int get_iteration() const
    {
        return iteration_;
    }
    
};
