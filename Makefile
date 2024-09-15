.PHONY: test install

CC=g++

test: src/arena.hpp test/test.cpp
	$(CC) -fsanitize=address -o test/test.out test/test.cpp
	./test/test.out

install: src/arena.hpp
	install src/arena.hpp /usr/include/arena_allocator
