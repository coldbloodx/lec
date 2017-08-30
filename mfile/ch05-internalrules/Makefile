#the file demostrates macro in make file
#macro is a variable, which could remove hard code and invoked by ${variablename}

#variables

#which compiler
CPP = g++

#rm command
RM = rm -f

#cp command
CP = cp

#cd command 
CD = cd

#where source files are put
LIBDIR = lib

#compiler switches
CPPDEBUG = -g -Wall -ansi

#objects for all source file under directory lib
OBJS = $(LIBDIR)/addition.o $(LIBDIR)/subtraction.o $(LIBDIR)/multiplication.o $(LIBDIR)/division.o
	
main: main.o $(OBJS)
	$(CPP) -o main $(OBJS) main.o

clean:
	$(RM) *.o main lib/*.o

install: main
	${CP} main ~/

uninstall:
	$(RM) ~/main
