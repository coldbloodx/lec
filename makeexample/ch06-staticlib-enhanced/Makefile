#pay attention to the following lines
LIBS = operation.a
CPP = g++ -g
LIBDIR = lib
RM = rm -f
CP = cp
AR = ar
AR_FLAGS = rv
OBJS = $(LIBDIR)/addition.o $(LIBDIR)/subtraction.o $(LIBDIR)/multiplication.o $(LIBDIR)/division.o main.o

all: main.o $(LIBS) 

$(LIBS): $(OBJS)
	ar -rv $@ $(OBJS)

clean:
	$(RM) $(OBJS) $(LIBS) main  
	
install:main
	${CP} main ~/

uninstall:
	$(RM) ~/main
