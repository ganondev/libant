#ifndef LIBANT_LIBANT_GRID
#define LIBANT_LIBANT_GRID

#include <Python.h>
#include <structmember.h>

#include <anttype.h>

typedef struct py_grid py_grid;

struct py_grid
{

	PyObject_HEAD
	ant_grid_t * grid;

};

PyGetSetDef grid_getsetters[];

PyTypeObject py_grid_type;

void grid_dealloc(py_grid *);

#endif
