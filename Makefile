CXX=clang++
CXXFLAGS=-O3 -Weverything -Werror -pedantic -std=c++11
CXXFLAGS+=-Wno-c++98-compat -Wno-missing-prototypes -Wno-padded

TARGETS=gloves rooms

all: ${TARGETS}

clean:
	rm -f ${TARGETS}
