#ifndef PY_GRID_CARTESIAN_H
#define PY_GIRD_CARTESIAN_H

#include <Python.h>
#include <structmember.h>

#include "libant_grid.h"

#define py_grid_cartesian_check(obj) PyObject_TypeCheck(obj, &py_grid_cartesian_type)

PyTypeObject py_grid_cartesian_type;

#endif
