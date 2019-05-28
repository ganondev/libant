#ifndef PY_ANT_2D_CARTESIAN_H
#define PY_ANT_2D_CARTESIAN_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include "anttype.h"
#include "antalgo.h"

#include "libant_py_ant.h"

PyTupleObject * ant_2d_cart_get_position(py_ant *, void *);

PyLongObject * ant_2d_cart_get_orientation(py_ant *, void*);

int ant_2d_cart_set_position(py_ant *, PyTupleObject *, void *);

int ant_2d_cart_set_orientation(py_ant *, PyObject *, void *);

PyObject * ant_2d_cart_new(PyTypeObject *, PyObject *, PyObject *);

int ant_2d_cart_init(py_ant *, PyObject *, PyObject *);

void ant_2d_cart_dealloc(py_ant *);

#ifndef _WIN32
static
#endif
PyGetSetDef ant_2d_cart_getsetters[];

PyTypeObject py_ant_2d_cartesian_type;

#endif
