CXX = g++
CXXFLAGS = -std=gnu++17
LDLIBS = -lGL -lGLEW -lglut -lSDL2 # this seems not to work; do take note that the first makefile, $Makefile_old, did not actually link the object files, it made no executable during or at the end of its execution
LOADLIBES= $(LDLIBS)	# nor is it this one
LIBS = $(LDLIBS)	# nor this
LIBXX

all: this_file_is_always_old
this_file_is_always_old: a.out
a.out: main.o triangle.o
	g++ main.o triangle.o -o a.out # -lGL -lGLEW -lglut -lSDL2
main.o: main.cpp
#	g++ -c main.cpp	# it has become apparent that when these commands are executed, there is nothing done intrinsically by $make relative to the specified flags (and probably even the libraries ?!); these are ~ "raw commands"; if the environment variables are to be used, they will be used implicitly (?!) apparently AFTER the raw commands have been used, and only if the target file still does not exist / "target condition still not satisfied" (?!)
triangle.o: triangle.cpp triangle.hpp
#	g++ -c triangle.cpp
clean: 
	rm a.out
	rm *.o
#	rm *.s
