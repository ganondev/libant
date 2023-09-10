#pragma once

#include "node.h"
#include "../grid.h"

class quadtree : public grid
{
public:

    node* root;

    quadtree() : grid(), root(new node(0, 0, nullptr))
    {
    }

    cell * get_cell(int64_t x, int64_t y) override
    {
        return node::find(root, x, y);
    }

    void insert(int64_t x, int64_t y, void * val) override
    {
        node::put_child(root, x, y, val);
    }
    
};
