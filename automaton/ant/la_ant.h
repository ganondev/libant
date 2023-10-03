#pragma once
#include <cstdint>
#include <vector>

#include <spatial_structure/la_cell.h>

constexpr int NORTH_2D[2] = {0, -1};
constexpr int EAST_2D[2] = {1, 0};
constexpr int SOUTH_2D[2] = {0, 1};
constexpr int WEST_2D[2] = {-1, 0};

inline const int * CARDINAL_2D[4] = {NORTH_2D, EAST_2D, SOUTH_2D, WEST_2D};

struct la_ant
{

    virtual ~la_ant() = default;

    //position as vector
    std::vector<int64_t> position;

    //orientation
    uint64_t orientation = 0;

    // constructor that basically combines resize_ant_position and zero_ant_position
    explicit la_ant(const size_t position_size)
    {
        position.resize(position_size);
    }

    // copy constructor
    la_ant(const la_ant& other)
    {
        position = other.position;
        orientation = other.orientation;
    }

    // move constructor
    la_ant(la_ant&& other) noexcept
    {
        position = std::move(other.position);
        orientation = other.orientation;
    }

    // copy assignment operator
    la_ant& operator=(const la_ant& other) = default;

    // move assignment operator
    la_ant& operator=(la_ant&& other) noexcept = default;

    // method with a similar signature to ant_directivefn
    virtual void directive(la_cell& cell) = 0;
    
};

// subclass of ant that implements langton's ant as the directive
struct langtons_ant : la_ant
{

    // default constructor
    langtons_ant() : la_ant(2) {}

    // based on langtons_ant_default_directive
    void directive(la_cell& cell) override
    {
        const auto value = cell.value;
        cell.value = !value;

        orientation = (orientation + (value ? 1 : -1)) % 4;

        position[0] += CARDINAL_2D[orientation][0];
        position[1] += CARDINAL_2D[orientation][1];
    }

};