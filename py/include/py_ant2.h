#ifndef PY_ANT2_H
#define PY_ANT2_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include "libant_py_ant.h"

int ant2_set_position(py_ant *, PyTupleObject *, void *);

PyObject * ant2_new(PyTypeObject *, PyObject *, PyObject *);

int ant2_init(py_ant *, PyObject *, PyObject *);

void ant2_dealloc(py_ant *);

#ifndef _WIN32
static
#endif
PyGetSetDef ant2_getsetters[];

PyTypeObject py_ant2_type;

#endif
