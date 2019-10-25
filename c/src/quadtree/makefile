all:
	c99 -Wall -c -I../../include -I. quadtree.c -o quadtree.o

test:
	c99 -DTREEBUG -I. -I../../include ../grid.c quadtree.c _test.c -lmcheck -o tests
	./tests
	rm tests

clean:
	rm quadtree.o
