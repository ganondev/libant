#pragma once

#include "node.h"
#include "../spatial_structure.h"

class quadtree : public spatial_structure
{
protected:
    node * get_cell_impl(const coords coords) override
    {
        return node::find(root, coords.x, coords.y);
    }
    node * insert_impl(const coords coords, const int val) override
    {
        return node::put_child(root, coords.x, coords.y, val);
    }
public:
    node * root;

    quadtree(const coords bounds={}) : spatial_structure(bounds), root(new node(0, 0, 0))
    {
    }
};
