debug:
	mkdir -p build
	c99 -Wall -fPIC -shared -Iinclude -Isrc src/*.c -o build/libant.so -D LIBANT_DEBUG

test: grid #test_quadtree
	c99 -Wall -lmcheck -Iinclude -Isrc test.c grid.o -O2 -o tests
	./tests
	rm tests *.o

grid:
	c99 -Wall -c -Iinclude src/grid.c -o grid.o

quadtree:
	c99 -Wall -c -Iinclude src/quadtree/quadtree.c -o quadtree.o

test_quadtree:
	cd src/quadtree && make test

