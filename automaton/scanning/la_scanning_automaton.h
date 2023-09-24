#pragma once
#include <functional>

#include "../la_automaton.h"

class la_scanning_automaton : public la_automaton
{
    using mapper_fn_t = std::function<int(int64_t, int64_t, la_cell, la_spatial_structure *)>;

    mapper_fn_t mapper_;
    
protected:
    std::vector<positional_diff> do_tick() override
    {
        const auto space_copy = space_->clone();
        std::vector<positional_diff> diffs;
        for (auto [x, y, opt_cell] : *space_)
        {
            la_cell& cell_ref = opt_cell.has_value() ? opt_cell.value().get() : space_->insert(x, y, 0);
            const int64_t old_value = cell_ref.value;
            const int result = mapper_(x, y, cell_ref, space_copy.get());
            cell_ref.value = result;
            if (old_value != cell_ref.value)
            {
                diffs.push_back({x, y, old_value, cell_ref.value});
            }
        }
        return diffs;
    }
    
public:
    la_scanning_automaton(la_spatial_structure * space, mapper_fn_t mapper_fn) :
        la_automaton(space), mapper_(std::move(mapper_fn)) {}
    
};
