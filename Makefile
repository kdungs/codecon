CXX=clang++
CXXFLAGS=-O3 -Weverything -Werror -pedantic -std=c++11
CXXFLAGS+=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-missing-prototypes -Wno-padded

SOURCES=$(wildcard src/*.cc)
TARGETS=$(patsubst src/%.cc,bin/%,$(SOURCES))

all: bin ${TARGETS}

bin:
	mkdir -p bin/

bin/%: src/%.cc
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -rf bin/
