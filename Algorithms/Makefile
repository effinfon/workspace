CPPFLAGS=$(shell sdl2-config --cflags) -std=gnu++17 $(EXTRA_CPP_FLAGS)
LDLIBS=-lbenchmark -lpthread -lGL -lglut -lX11 -lSDL2 -lGLEW -$(EXTRA_LDLIBS)
EXTRA_LDLIBS?=lGL
all: main triangle
clean:
	pwd
	rm -f $(find | grep "\.o")
.PHONY: all clean
