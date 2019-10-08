debug:
	mkdir -p build
	c99 -Wall -fPIC -fgnu89-inline -shared -Iinclude src/*.c -o build/libant.so

test: anttype #test_quadtree
	c99 -Wall -Iinclude test.c anttype.o quadtree.o -o tests
	./tests
	rm tests

anttype: quadtree
	c99 -Wall -c -Iinclude src/anttype.c -o anttype.o

quadtree:
	c99 -Wall -c -Iinclude src/quadtree/quadtree.c -o quadtree.o

test_quadtree:
	cd src/quadtree && make test

