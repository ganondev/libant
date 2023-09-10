#pragma once
#include <cstdint>
#include <vector>

#include "cell.h"

// We will be converting what was in the include/ant.h file to an object oriented design

struct ant
{

    virtual ~ant() = default;

    //position as vector
    std::vector<int64_t> position;

    //orientation
    uint64_t orientation = 0;

    // constructor that basically combines resize_ant_position and zero_ant_position
    explicit ant(const size_t position_size)
    {
        position.resize(position_size);
    }

    // copy constructor
    ant(const ant& other)
    {
        position = other.position;
        orientation = other.orientation;
    }

    // move constructor
    ant(ant&& other) noexcept
    {
        position = std::move(other.position);
        orientation = other.orientation;
    }

    // copy assignment operator
    ant& operator=(const ant& other) = default;

    // move assignment operator
    ant& operator=(ant&& other) noexcept = default;

    // method with a similar signature to ant_directivefn
    virtual void directive(cell& cell) = 0;
    
};

// subclass of ant that implements langton's ant as the directive
struct langtons_ant : ant
{

    // default constructor
    langtons_ant() : ant(2) {}

    // based on langtons_ant_default_directive
    void directive(cell& cell) override;

};