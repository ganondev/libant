from distutils.core import setup, Extension

sources = [	r'./src/libant_py_ant.c',
			r'./src/libant_py_module.c',
			r'./src/py_ant2.c',
			r'./src/py_ant3.c',
			r'../c/anttype.c',
			r'../c/antalgo.c' ]

includes = [r'./include/', r'../c/']

setup(name='libant',
		version='0.1',
		ext_modules=[Extension('libant',
							sources,
							include_dirs=includes
							)
				]
	)
