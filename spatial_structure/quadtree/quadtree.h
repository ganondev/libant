#pragma once

#include "node.h"
#include "../spatial_structure.h"

class quadtree : public spatial_structure
{
public:

    node * root;

    quadtree() : spatial_structure(), root(new node(0, 0, nullptr))
    {
    }

    node * get_cell(int64_t x, int64_t y) override
    {
        return node::find(root, x, y);
    }

    node * insert(int64_t x, int64_t y, void * val) override
    {
        return node::put_child(root, x, y, val);
    }
    
};
