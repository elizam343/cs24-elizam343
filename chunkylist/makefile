CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

main: main.o ChunkyList.o MyChunkyList.o MyChunkyNode.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp ChunkyList.h ChunkyNode.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

ChunkyList.o: ChunkyList.cpp ChunkyList.h ChunkyNode.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

MyChunkyList.o: MyChunkyList.cpp MyChunkyList.h MyChunkyNode.h ChunkyList.h ChunkyNode.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

MyChunkyNode.o: MyChunkyNode.cpp MyChunkyNode.h ChunkyNode.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f main main.o ChunkyList.o MyChunkyList.o MyChunkyNode.o
