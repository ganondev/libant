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

    class SpatialStructureIterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::tuple<int64_t, int64_t, std::optional<std::reference_wrapper<la_cell>>>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        SpatialStructureIterator(la_spatial_structure* ss, int64_t x, int64_t y)
            : ss_(ss), x_(x), y_(y) {}

        value_type operator*() {
            return std::make_tuple(x_, y_, ss_->get_cell(x_, y_));
        }

        SpatialStructureIterator& operator++() {
            // Increment the x coordinate
            ++x_;

            // If x is out of bounds, reset x and increment y
            auto extents = ss_->get_extents(); 
            if (x_ >= extents.x + 1) {
                x_ = 0;
                ++y_;
            }

            // If y is out of bounds, you've finished iterating
            // Optionally set some kind of "end" flag if you want to implement a check in operator!=

            return *this;
        }

        bool operator!=(const SpatialStructureIterator& other) {
            // return !(x_ == other.x_ && y_ == other.y_);
            return y_ <= other.y_;
        }

    private:
        la_spatial_structure* ss_;
        int64_t x_;
        int64_t y_;
    };

    using opt_cell = std::optional<std::reference_wrapper<la_cell>>;
    
    coords bounds_;
protected:
    virtual opt_cell get_cell_impl(coords coords) = 0;
    virtual la_cell& insert_impl(coords coords, int val) = 0;

    la_spatial_structure(const la_spatial_structure& other) = default;
    
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

    // TODO this should not be opt_cell, it should be guaranteed
    [[nodiscard]]
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

    [[nodiscard]]
    virtual std::unique_ptr<la_spatial_structure> clone() = 0;
    // virtual la_spatial_structure * clone() = 0;

    using iterator = SpatialStructureIterator;
    
    iterator begin() {
        return {this, 0, 0};
    }

    iterator end() {
        auto extents = get_extents();
        return {this, extents.x, extents.y};
    }

    int get_num_neighbors(int64_t x, int64_t y)
    {
        int num_neighbors = 0;
        for (int64_t dx = -1; dx <= 1; dx++)
        {
            for (int64_t dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                {
                    continue;
                }
                num_neighbors += get_value(x + dx, y + dy);
            }
        }
        return num_neighbors;
    }

    [[nodiscard]]
    coords get_bounds() const
    {
        return bounds_;
    }

    virtual coords get_extents() = 0;
};

