#Makefile para main.c en linux, si se encuentran en MACOS o Windows 
#revisen que banderas de compilación deben estar en LDLIBS para
#que compile correctamente.

CC = g++

LDLIBS = -lglut -lGL -lGLU -lXxf86vm -std=c++11 -lm

PROG = prog

end:
	$(CC) main.cc $(LDLIBS) -o $(PROG)


