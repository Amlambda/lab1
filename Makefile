########################################################################
# Makefile for MPItutorial
#
########################################################################

CC         =  mpicc
CCFLAGS    =  -O3
LIBS       =  -lmpi -lm

all:
	@echo "Usage: make hello"

hello:          hello.c
	$(CC) $(CCFLAGS) -o hello hello.c $(LIBS)

exchange:       exchange.c
	$(CC) $(CCFLAGS) -o exchange exchange.c $(LIBS)

pingpong:       pingpong.c
	$(CC) $(CCFLAGS) -o pingpong pingpong.c $(LIBS)

onetoall:          onetoall.c
	$(CC) $(CCFLAGS) -o onetoall onetoall.c $(LIBS)

integral:             integral.c
	$(CC) $(CCFLAGS) -o integral integral.c $(LIBS)

integral2d:             integral2d.c
	$(CC) $(CCFLAGS) -o integral2d integral2d.c $(LIBS)


clean:
	$(RM) hello exchange pingpong onetoall integral integral2d


