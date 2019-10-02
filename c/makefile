debug:
	mkdir -p build
	c99 -fPIC -fgnu89-inline -shared -Iinclude src/*.c -o build/libant.so

test:
	cd src/quadtree && make test
