#pragma once
#include <cstdint>
#include <cstdlib>

#include "../cell.h"

enum relative_quadrant {

    EQ = -1,
    NE = 0,
    NW = 1,
    SW = 3,
    SE = 2

};

// quadtree node extending cell
class node : public cell 
{
    
    int64_t x;
    int64_t y;
    bool is_leaf;

public:

    node* children[4] = {nullptr, nullptr, nullptr, nullptr};
    
    node(int64_t x, int64_t y, void * in_value) : cell(), x(x), y(y), is_leaf(true)
    {
        this->value = in_value;
    }

    node* get_child(relative_quadrant quadrant)
    {
        return children[quadrant];
    }

    relative_quadrant get_relative_quadrant(int64_t rel_x, int64_t rel_y) const
    {
        if (this->y == rel_y && this->x == rel_x) return EQ;

        const bool vertical = this->y > rel_y;
        const bool horizontal = this->x > rel_x;

        return static_cast<relative_quadrant>(vertical * 2 | horizontal);
    }
    
    relative_quadrant compare(const node& other) const
    {
        return get_relative_quadrant(other.x, other.y);
    }

    // TODO might just make this a derived property
    void split()
    {
        is_leaf = false;
    }
    
    static node * find(node * root, int64_t in_x, int64_t in_y)
    {

        relative_quadrant quadrant = root->get_relative_quadrant(in_x, in_y);
        if (quadrant == EQ)
        {
            return root;
        }
        node * current_parent = root;
        while (true)
        {
            if (current_parent->is_leaf)
            {
                // cell not found - parent has no children
                return nullptr;
            }
            current_parent = current_parent->get_child(quadrant);
            if (current_parent == nullptr)
            {
                // cell not found - parent has no child in quadrant
                return nullptr;
            }
            quadrant = current_parent->get_relative_quadrant(in_x, in_y);
            if (quadrant == EQ)
            {
                return current_parent;
            }
        }
    }

    // put_child
    static void put_child(node * parent, int64_t x, int64_t y, void * in_value)
    {

        node * current_parent = parent;
        while (true)
        {

            relative_quadrant quadrant = current_parent->get_relative_quadrant(x, y);
            
            // update current_parent value in place to simulate replacement
            if (quadrant == EQ)
            {
                if (current_parent->value)
                {
                    free(current_parent->value);
                }
                current_parent->value = in_value;
                return;
            }

            // Destination is this node
            if (current_parent->is_leaf)
            {
                current_parent->split();
                current_parent->children[quadrant] = new node(x, y, in_value);
                return;
            }

            // Destination is relative child node
            node * child = current_parent->get_child(quadrant);
            if (!child)
            {
                current_parent->children[quadrant] = new node(x, y, in_value);
                return;
            }

            // keep searching
            current_parent = child;
            
        }
        
    }
    
};
