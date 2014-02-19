CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -fno-elide-constructors -g
LINK.o = $(LINK.cc)


all:main

main.o: main.cpp

main: main.o 

clean:
	rm -f *.o
