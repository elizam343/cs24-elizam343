CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

.PHONY: clean all

all: genepool testprog

genepool: main.o GenePool.o Person.o Query.o
	${CXX} $(CXXFLAGS) -o $@ $+

testprog: test.o GenePool.o Person.o Query.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp GenePool.h Person.h Query.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

GenePool.o: GenePool.cpp GenePool.h Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Person.o: Person.cpp Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Query.o: Query.cpp Query.h GenePool.h Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

test.o: test.cpp GenePool.h Person.h Query.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f genepool testprog main.o GenePool.o Person.o Query.o test.o
