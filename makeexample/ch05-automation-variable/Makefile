LIBDIR = lib
CPP = g++
FLAGS = -g
RM = rm -f 
OBJS = main.o $(LIBDIR)/addition.o $(LIBDIR)/division.o $(LIBDIR)/multiplication.o $(LIBDIR)/subtraction.o

all: $(OBJS) 
	$(CPP) $(FLAGS) -o $@ $(OBJS)
	
clean:
	$(RM) $(OBJS) all
