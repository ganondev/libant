#pragma once

#include "la_node.h"
#include "../la_spatial_structure.h"

class la_quadtree : public la_spatial_structure
{
protected:
    std::optional<std::reference_wrapper<la_cell>> get_cell_impl(coords coords) override
    {
        if (la_node * nd = la_node::find(root, coords.x, coords.y))
        {
            return {*nd};  // Assuming node is a subclass of cell
        }
        return std::nullopt;
    }
    la_node& insert_impl(const coords coords, const int val) override
    {
        return *la_node::put_child(root, coords.x, coords.y, val);
    }
public:
    // TODO move this out of public
    la_node * root;

    la_quadtree(const coords bounds={}) : la_spatial_structure(bounds), root(new la_node(0, 0, 0))
    {
    }

    std::unique_ptr<la_spatial_structure> clone() override
    {
        auto new_quadtree = std::make_unique<la_quadtree>(get_bounds());
        new_quadtree->root = root->deep_clone(); // Assuming you implement a deep_clone() method in la_node
        return new_quadtree;
    }

    coords get_extents() override
    {
        // TODO this will need to derive the bounds, but it can't because extents only
        // looks at max extends, and assumes a min extent of 0
        return get_bounds();
    }
};
