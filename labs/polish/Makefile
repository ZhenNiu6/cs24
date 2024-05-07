CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter

all: test

test: main.o AST.o Nodes.o Stack.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

AST.o: AST.cpp 
	${CXX} $(CXXFLAGS) -c -o $@ $<

Nodes.o: Nodes.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

Stack.o: Stack.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o test