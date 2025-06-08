WFlags = -Wall -Wextra -pedantic

# Default target: build both executable
all: test interface

# Build test executable
test: test.o code.o
	g++ $(WFlags) -g test.o code.o -o test

test.o: u3a_test.cpp u3a.h
	g++ $(WFlags) -g -c u3a_test.cpp -o test.o

# Build interface executable
interface: interface.o code.o
	g++ $(WFlags) -g interface.o code.o -o interface

interface.o: interface.cpp u3a.h
	g++ $(WFlags) -g -c interface.cpp -o interface.o

# Shared code object
code.o: code.cpp u3a.h
	g++ $(WFlags) -g -c code.cpp -o code.o

# Clean build artifacts
clean:
	rm -f test interface *.o