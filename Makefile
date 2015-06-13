CXX=clang++
CXXFLAGS=-O3 -Weverything -Werror -pedantic -std=c++11
CXXFLAGS+=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-missing-prototypes -Wno-padded

TARGETS=base_arithmetic palindronum mug gloves rooms

all: ${TARGETS}

clean:
	rm -f ${TARGETS}
