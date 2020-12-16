CPPFLAGS=$(shell sdl2-config --cflags) -std=gnu++17 $(EXTRA_CPP_FLAGS)
LDLIBS=-lbenchmark -lpthread -lGL -lglut -lX11 -lSDL2 -lGLEW -$(EXTRA_LDLIBS)
EXTRA_LDLIBS?=lGL

# the labels are called "targets"; not specifying an argument to make will invoke the first target in the file (?)

main: main.o
triangle: main.cpp triangle.cpp	
	g++ -c main.cpp triangle.cpp	# (!?) it is rather problematic to handle the dependencies of compilation units
			# that include other compilation units, because they have to be written together like this; and
			# what about their object files, do those leave any signs of this dependency (?) [easy to use signs, of course]
clean:
	pwd
#	rm -f $(find | grep "\.o")	# this is too general; what if there are ~ "external object files" (!?) 
		# why doesn't the above expression work (?); even the comment (seems to) get interpreted by $make this way, why (?!)
#	rm obj/Debug/*.o	# how to tell it that it can fail to find files, but it shouldn't produce an error and terminate (!?)
	rm *.o
	rm -r build
install:

main.o: main.cpp
	g++ -c main.cpp	# I wonder if those flags above will go to all files mentioned here (?)
			# well, in a normal project in CodeBlocks it would happen the same, so maybe yes
			# but, that begs the question: what if different libraries are to be used with different
			# parts of the project (?!)
triangle.o: triangle.cpp
	g++ -c triangle.cpp
OpenGL: main.o triangle.o move
main.o: main.cpp triangle.cpp	# it seems that I only need to put the dependency of compilation units here, not necessarely write them down in the compilation command myself (!?)
#	g++ -c main.cpp # triangle.cpp	# further, it doesn't seem like I even have to write these commands at all; they might get overriden, in certain cases, probable (?!)
triangle.o: main.cpp triangle.cpp
#	g++ -c triangle.cpp # main.cpp 
move: # main.o triangle.o
	mkdir build	
	mv *.o build	# now, what about directly compiling them there (!?)
.PHONY: all clean

### TD
# whenever compiling, create a new folder with the "version number" and timestamp as a name, and in there place all files obtained through compilation
# create the assembly of each source code file, and do not delete it; place them in an asm sub-folder that mimics the structure of the project
# compile static libraries of everything, as well as dynamic libraries; place them in sub-folders s-lib and d-lib, respectively
# targets can be "buried" hierarchically in folders, but this script will look for them
# the convenience of a "build" sub-folder
# all object files will be compiled into some sub-folder, not directly in the root folder (!); it's a mess otherwise
# 

#all: program
program: main.o Function1.o Function2.o
#main.o: main.cpp
	g++ -c main.cpp
Function1.o: Function1.cpp
	g++ -c Function1.cpp
Function2.o: Function2.cpp
	g++ -c Function2.cpp
#clean:
#	rm main.o Function1.o Function2.o	# fully specified lists like these are preferable, but with some search-around (maybe) and also an auto-generation of them

