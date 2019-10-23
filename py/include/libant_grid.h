#ifndef LIBANT_LIBANT_GRID
#define LIBANT_LIBANT_GRID

#include <Python.h>
#include <structmember.h>

#include <grid.h>

#define py_grid_check(obj) PyObject_TypeCheck(obj, &py_grid_type)

typedef struct py_grid py_grid;

struct py_grid
{

	PyObject_HEAD
	ant_grid_t * grid;

};

PyTypeObject py_grid_type;

#endif
