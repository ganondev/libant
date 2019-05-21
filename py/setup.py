from distutils.core import setup, Extension

setup(name='libant',
		version='0.1',
		ext_modules=[Extension('libant',
							[r'libant_py_def.c', r'../c/anttype.c'],
							include_dirs=[r'.', r'../c/']
							)
				]
	)
