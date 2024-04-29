CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter

all: test

test: test.o Tree.o Node.o
	${CXX} $(CXXFLAGS) -o $@ $+

test.o: test.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

Tree.o: Tree.cpp Tree.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Node.o: Node.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o test