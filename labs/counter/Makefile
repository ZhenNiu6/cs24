CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

counter: main.o Counter.o List.o Index.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp List.h Counter.h Index.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

List.o: List.cpp List.h 
	${CXX} $(CXXFLAGS) -c -o $@ $<

Counter.o: Counter.cpp Counter.h Index.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Index.o: Index.cpp Index.h 
	${CXX} $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f counter main.o Counter.o List.o Index.o