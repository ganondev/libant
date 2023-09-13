#pragma once

// abstract Cell class
class cell
{
public:
    virtual ~cell() = default;

    void * value;
    int state; //TODO consider if state is needed

    // allows ants to have 'dynamic' directives based on the cell they are on
    // currently unused, probably needs a return value or to take a reference to the ant
    // virtual void rule() = 0;
    
};
