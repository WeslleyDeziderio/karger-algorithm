PROJ_NAME=min-cut

#.hpp files
HPP_SOURCE=$(wildcard ./include/*.hpp ./include/utils/*.hpp)

# .cpp files
CPP_SOURCE=$(wildcard ./src/*.cpp ./src/utils/*.cpp)

# Object files
OBJ=$(CPP_SOURCE:.c=.o)

# compiler and linker
CXX=g++

#compiler's flags
CXXFLAGS= -Wall -Wextra --std=c++23 -g
		
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using G++ linker: $@'
	$(CXX) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objects/%.o: ./src/%.cpp ininclude/%.hpp
	@ echo 'Building target using G++ compiler: $<'
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '

./objects/main.o: ./src/main.cpp $(HPP_SOURCE)
	@ echo 'Building target using G++ compiler: $<'
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects

.PHONY: all clean