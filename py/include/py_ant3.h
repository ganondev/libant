#ifndef PY_ANT3_H
#define PY_ANT3_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include "libant_py_ant.h"

int ant3_set_position(py_ant *, PyTupleObject *, void *);

int ant3_init(py_ant *, PyObject *, PyObject *);

#ifndef _WIN32
static
#endif
PyGetSetDef ant3_getsetters[];

PyTypeObject py_ant3_type;

#endif
