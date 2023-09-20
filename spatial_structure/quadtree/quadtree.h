#pragma once

#include "node.h"
#include "../spatial_structure.h"

class quadtree : public spatial_structure
{
protected:
    std::optional<std::reference_wrapper<cell>> get_cell_impl(coords coords) override
    {
        if (node * nd = node::find(root, coords.x, coords.y))
        {
            return {*nd};  // Assuming node is a subclass of cell
        }
        return std::nullopt;
    }
    node& insert_impl(const coords coords, const int val) override
    {
        return *node::put_child(root, coords.x, coords.y, val);
    }
public:
    // TODO move this out of public
    node * root;

    quadtree(const coords bounds={}) : spatial_structure(bounds), root(new node(0, 0, 0))
    {
    }
};
