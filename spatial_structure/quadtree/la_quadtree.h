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
    // la_quadtree * clone() override
    {
        // TODO
        return nullptr;
    }
};
