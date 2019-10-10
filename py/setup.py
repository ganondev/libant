from distutils.core import setup, Extension

sources = [	r'./src/libant_py_ant.c',
			r'./src/libant_py_module.c',
			r'./src/py_ant2.c',
			r'./src/py_ant3.c',
			r'./src/py_langtons_ant.c',
			r'./src/libant_grid.c',
			r'../c/src/grid.c',
			r'../c/src/antalgo.c',
			r'../c/src/quadtree/quadtree.c']

includes = [ r'./include/', r'../c/include', r'../c/src', r'../c/src/quadtree' ]

setup(name='libant',
		version='0.1',
		ext_modules=[Extension('libant',
							sources,
							include_dirs=includes,
							extra_compile_args=["-DLIBANT_DEBUG",]
							)
				]
	)
