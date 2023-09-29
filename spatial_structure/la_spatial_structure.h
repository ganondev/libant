#pragma once
#include <optional>

#include "la_cell.h"

struct coords
{
    int64_t x;
    int64_t y;

    [[nodiscard]] 
    coords up(const int by=1) const
    {
        return {x, y + by};
    }

    [[nodiscard]] 
    coords down(const int by=1) const
    {
        return {x, y - by};
    }

    [[nodiscard]] 
    coords left(const int by=1) const
    {
        return {x - by, y};
    }

    [[nodiscard]] 
    coords right(const int by=1) const
    {
        return {x + by, y};
    }

    [[nodiscard]]
    coords up_left(const int by=1) const
    {
        return {x - by, y + by};
    }

    [[nodiscard]]
    coords up_right(const int by=1) const
    {
        return {x + by, y + by};
    }

    [[nodiscard]]
    coords down_left(const int by=1) const
    {
        return {x - by, y - by};
    }

    [[nodiscard]]
    coords down_right(const int by=1) const
    {
        return {x + by, y - by};
    }
    
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
    coords project(const int64_t in_x, const int64_t in_y) const
    {
        return project({in_x, in_y});
    }

    [[nodiscard]]
    coords project(const coords in_coords) const
    {
        const coords s {
            bounds_.x == 0 ? in_coords.x : ((in_coords.x % bounds_.x) + bounds_.x) % bounds_.x,
            bounds_.y == 0 ? in_coords.y : ((in_coords.y % bounds_.y) + bounds_.y) % bounds_.y,
        };
        return s;
    }

    // TODO this should not be opt_cell, it should be guaranteed
    [[nodiscard]]
    opt_cell get_cell(const int64_t x, const int64_t y)
    {
        return get_cell({x, y});
    }

    [[nodiscard]]
    opt_cell get_cell(const coords coords)
    {
        return get_cell_impl(project(coords));
    }

    // get value from cell
    [[nodiscard]]
    int get_value(const int64_t x, const int64_t y)
    {
        return get_value({x, y});
    }

    [[nodiscard]]
    int get_value(const coords coords)
    {
        if (const auto opt_cell = get_cell(coords); opt_cell)
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

    [[nodiscard]]
    virtual std::vector<std::vector<int>> get_cells_around(const coords& center_coord, const int radius=1)
    {
        std::vector<std::vector<int>> result;
        // Loop through each row within the radius.
        for(int dy = -radius; dy <= radius; ++dy) {
            std::vector<int> row;
            // Loop through each column within the radius.
            for(int dx = -radius; dx <= radius; ++dx) {
                // Use your helper methods for getting the new coordinates.
                const coords new_coord = center_coord.right(dx).up(dy);
                // Assume get_cell_value returns int.
                int cell_value = get_value(new_coord);
                row.push_back(cell_value);
            }
            result.push_back(row);
        }
        return result;
    }

    [[nodiscard]]
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
                num_neighbors += (get_value(x + dx, y + dy) ? 1 : 0);
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

