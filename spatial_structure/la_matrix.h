﻿#pragma once
#include "la_spatial_structure.h"
#include "../submodules/eigen/Eigen/Dense"

class la_matrix : public la_spatial_structure
{

    using cell_matrix = Eigen::Matrix<la_cell, Eigen::Dynamic, Eigen::Dynamic>; 
    
    cell_matrix matrix;

protected:
    std::optional<std::reference_wrapper<la_cell>> get_cell_impl(coords coords) override
    {
        return {matrix.coeffRef(coords.x, coords.y)};
    }

    la_cell& insert_impl(coords coords, int val) override
    {
        matrix(coords.x, coords.y) = la_cell{val};
        return matrix.coeffRef(coords.x, coords.y);
    }
    
public:
    la_matrix(const coords bounds) : la_spatial_structure(bounds)
    {

        matrix = cell_matrix::Zero(bounds.x, bounds.y);
        
    }
    
};