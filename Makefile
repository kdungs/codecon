CXX=clang++
CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11

all: gloves rooms test

test:
	@python tests.py

clean:
	rm -f gloves
	rm -f rooms
