debug:
	c99 -Wall -D LIBANT_DEBUG -fgnu89-inline -I../c/include -I./include -I/usr/include/python3.7 -shared -o libant.so -fPIC ../c/src/anttype.c ../c/src/antalgo.c ./src/libant_py_ant.c ./src/libant_py_module.c ./src/py_ant2.c ./src/py_ant3.c ./src/py_langtons_ant.c

all: module py_ant antalgo anttype
	c99 -Wall *.o -shared -o libant.so
	rm -rf *.o

module:
	c99 -Wall -fPIC -I./include -I/usr/include/python3.7 -I../c -c src/libant_py_module.c -o module.o

py_ant:
	c99 -Wall -fPIC -I./include -I/usr/include/python3.7 -I../c -c src/libant_py_ant.c -o py_ant.o

antalgo:
	c99 -Wall -fPIC -c ../c/antalgo.c -o antalgo.o

anttype:
	c99 -Wall -c ../c/anttype.c -o anttype.o

# todo antalgo and anttype should be moved to c/ makefile
