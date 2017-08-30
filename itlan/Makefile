.PHONY: clean
.PHONY: all

all: opcpp opc

opcpp: ut.cpp
	g++ ut.cpp -o opcpp

opc:test.o wrapper.o 
	gcc test.o wrapper.o -o opc

clean:
	rm -f opcpp opc *.o
