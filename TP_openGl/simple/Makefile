CXXFLAGS = -Wall -Wextra -g -std=c++11

simple: simple.o gl-utils.o
	  g++ $^ -o $@ -L/usr/lib/nvidia-384 -lglut -lGLEW -lGL

clean:
	@rm -f *o *~ simple

simple.o gl-utils.o: gl-utils.h
