#include "libant_py_module.h"
#include "py_ant2.h"
#include "py_langtons_ant.h"
#include "py_ant3.h"

#define ADD_OBJ_TO_MODULE(module, name, obj) Py_INCREF(obj); PyModule_AddObject(module, name, (PyObject *) obj);

PyMODINIT_FUNC PyInit_libant(void)
{

	PyObject *m;

	//Check if types are ready
	if (PyType_Ready(&py_ant_type) < 0) return NULL;
	py_ant2_type.tp_base = &py_ant_type;
	if (PyType_Ready(&py_ant2_type) < 0) return NULL;
	py_langtons_ant_type.tp_base = &py_ant2_type;
	if (PyType_Ready(&py_langtons_ant_type) < 0) return NULL;
	py_ant3_type.tp_base = &py_ant2_type;
	if (PyType_Ready(&py_ant3_type) < 0) return NULL;

    m = PyModule_Create(&libant);
    if (m == NULL) return NULL;

	//Constants
	PyObject * north_2d_tuple = PyTuple_Pack(2, PyLong_FromLong(NORTH_2D[0]), PyLong_FromLong(NORTH_2D[1]));
	ADD_OBJ_TO_MODULE(m, "NORTH_2D", north_2d_tuple);
	PyObject * south_2d_tuple = PyTuple_Pack(2, PyLong_FromLong(SOUTH_2D[0]), PyLong_FromLong(SOUTH_2D[1]));
	ADD_OBJ_TO_MODULE(m, "SOUTH_2D", south_2d_tuple);
	PyObject * west_2d_tuple = PyTuple_Pack(2, PyLong_FromLong(WEST_2D[0]), PyLong_FromLong(WEST_2D[1]));
	ADD_OBJ_TO_MODULE(m, "WEST_2D", west_2d_tuple);
	PyObject * east_2d_tuple = PyTuple_Pack(2, PyLong_FromLong(EAST_2D[0]), PyLong_FromLong(EAST_2D[1]));
	ADD_OBJ_TO_MODULE(m, "EAST_2D", east_2d_tuple);
	langtons_ant_directive_func = PyCFunction_New(&langtons_ant_directive, NULL);
	ADD_OBJ_TO_MODULE(m, "langtons_ant_directive", langtons_ant_directive_func);
	
	//Class Definitions
	ADD_OBJ_TO_MODULE(m, "Ant", &py_ant_type);
	ADD_OBJ_TO_MODULE(m, "Ant2", &py_ant2_type);
	ADD_OBJ_TO_MODULE(m, "LangtonsAnt", &py_langtons_ant_type);
	ADD_OBJ_TO_MODULE(m, "Ant3", &py_ant3_type);
	
    return m;

}
