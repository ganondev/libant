#pragma once
#include <cstdint>

#include "../la_cell.h"

enum relative_quadrant {

    EQ = -1,
    NE = 0,
    NW = 1,
    SW = 3,
    SE = 2

};

// quadtree node extending cell
class la_node : public la_cell 
{
    
    int64_t x_;
    int64_t y_;
    bool is_leaf_;

    la_node* children[4] = {nullptr, nullptr, nullptr, nullptr};

public:
    
    la_node(const int64_t x, const int64_t y, const int in_value) : la_cell(), x_(x), y_(y), is_leaf_(true)
    {
        this->value = in_value;
    }

    [[nodiscard]]
    la_node* get_child(const relative_quadrant quadrant) const
    {
        return children[quadrant];
    }

    [[nodiscard]]
    int get_child_count() const
    {
        return
            (get_child(NE) ? 1 : 0)
            + (get_child(NW) ? 1 : 0)
            + (get_child(SW) ? 1 : 0)
            + (get_child(SE) ? 1 : 0);
    }

    [[nodiscard]]
    relative_quadrant get_relative_quadrant(const int64_t rel_x, const int64_t rel_y) const
    {
        if (this->y_ == rel_y && this->x_ == rel_x) return EQ;

        const int vertical = this->y_ > rel_y ? 1 : 0;
        const int horizontal = this->x_ > rel_x ? 1 : 0;

        return static_cast<relative_quadrant>(vertical * 2 | horizontal);
    }

    [[nodiscard]]
    relative_quadrant compare(const la_node& other) const
    {
        return get_relative_quadrant(other.x_, other.y_);
    }

    // TODO might just make this a derived property
    void split()
    {
        is_leaf_ = false;
    }

    [[nodiscard]]
    static la_node * find(la_node * root, const int64_t in_x, const int64_t in_y)
    {

        relative_quadrant quadrant = root->get_relative_quadrant(in_x, in_y);
        if (quadrant == EQ)
        {
            return root;
        }
        la_node * current_parent = root;
        while (true)
        {
            if (current_parent->is_leaf_)
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
    
    static la_node * put_child(la_node * parent, const int64_t x, const int64_t y, const int in_value)
    {

        la_node * current_parent = parent;
        while (true)
        {

            relative_quadrant quadrant = current_parent->get_relative_quadrant(x, y);
            
            // update current_parent value in place to simulate replacement
            if (quadrant == EQ)
            {
                current_parent->value = in_value;
                return current_parent;
            }

            // Destination is this node
            if (current_parent->is_leaf_)
            {
                current_parent->split();
                const auto new_node = new la_node(x, y, in_value);
                current_parent->children[quadrant] = new_node;
                return new_node;
            }

            // Destination is relative child node
            la_node * child = current_parent->get_child(quadrant);
            if (!child)
            {
                const auto new_node = new la_node(x, y, in_value);
                current_parent->children[quadrant] = new_node;
                return new_node;
            }

            // keep searching
            current_parent = child;
            
        }
        
    }

    la_node* deep_clone() const
    {
        la_node* new_node = new la_node(this->x_, this->y_, this->value); // Assuming x_, y_, and value are member variables
        new_node->is_leaf_ = this->is_leaf_; // Copy the leaf status

        for (int i = 0; i < 4; ++i)
        {
            if (this->children[i])
            {
                new_node->children[i] = this->children[i]->deep_clone();
            }
        }

        return new_node;
    }
    
};
