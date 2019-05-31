from distutils.core import setup, Extension

sources = [	r'./src/libant_py_ant.c',
			r'./src/libant_py_module.c',
			r'./src/py_ant2.c',
			r'./src/py_ant3.c',
			r'./src/py_langtons_ant.c',
			r'../c/src/anttype.c',
			r'../c/src/antalgo.c',
			r'../dependencies/libdict/src/dict.c',
			r'../dependencies/libdict/src/hashtable_common.c',
			r'../dependencies/libdict/src/hashtable.c',
			r'../dependencies/libdict/src/hashtable2.c', ]

includes = [r'./include/', r'../c/include', r'../dependencies/libdict/include', r'../dependencies/libdict/src', ]

setup(name='libant',
		version='0.1',
		ext_modules=[Extension('libant',
							sources,
							include_dirs=includes
							)
				]
	)
