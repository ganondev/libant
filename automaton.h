#pragma once
#include "spatial_structure/spatial_structure.h"

// We will be converting what was in the include/grid.h file to an object oriented design


class automaton
{
protected:
    spatial_structure * space_;
public:
    
    automaton(spatial_structure * space) : space_(space) {}
    
    virtual ~automaton() = default;

    virtual void tick() = 0;
    
};
