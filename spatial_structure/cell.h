#pragma once

// abstract Cell class
class cell
{
public:
    virtual ~cell() = default;
    
    int value;

    // allows ants to have 'dynamic' directives based on the cell they are on
    // currently unused, probably needs a return value or to take a reference to the ant
    // virtual void rule() = 0;

    cell() = default;
    explicit cell(const int value): value(value) {}
};
