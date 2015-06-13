CXX=clang++
CXXFLAGS=-O3 -Weverything -Werror -pedantic -std=c++11
CXXFLAGS+=-Wno-c++98-compat -Wno-missing-prototypes -Wno-padded

all: gloves rooms test

test:
	@python tests.py

clean:
	rm -f gloves
	rm -f rooms
