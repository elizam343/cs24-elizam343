CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: test

test: test.o MyGrove.o StringGrove.o
	${CXX} $(CXXFLAGS) -o $@ $+

test.o: test.cpp MyGrove.h StringGrove.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

MyGrove.o: MyGrove.cpp MyGrove.h StringGrove.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

StringGrove.o: StringGrove.cpp StringGrove.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f test test.o MyGrove.o StringGrove.o
