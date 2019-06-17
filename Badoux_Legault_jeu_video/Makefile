CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter

hells_skulls: main.o event.o
	g++ $^ -o $@ -lIrrlicht

clean:
	@rm -f hells_skulls *.o
