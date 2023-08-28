# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Object files
OBJS = test.o CountyMap.o

# Target executable name
TARGET = county_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

test.o: test.cpp CountyMap.h County.h
	$(CXX) $(CXXFLAGS) -c test.cpp

CountyMap.o: CountyMap.cpp CountyMap.h
	$(CXX) $(CXXFLAGS) -c CountyMap.cpp

County.o: County.h
	$(CXX) $(CXXFLAGS) -c County.cpp

clean:
	rm -f *.o $(TARGET)
