ifeq ($(shell uname -s), Darwin)
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lm
endif
CC = g++
PROGRAMS = main
$(PROGRAMS).o :
	$(CC) $(PROGRAMS).cpp callbacks.cpp -o $(PROGRAMS) $(LDFLAGS)
clean:
	@rm -f $(PROGRAMS) *.o *.out core
