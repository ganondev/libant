#pragma once

// abstract Cell class
class la_cell
{
public:
    virtual ~la_cell() = default;
    
    int value;

    // allows ants to have 'dynamic' directives based on the cell they are on
    // currently unused, probably needs a return value or to take a reference to the ant
    // virtual void rule() = 0;

    la_cell() = default;
    explicit la_cell(const int value): value(value) {}
};
