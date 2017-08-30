OBJS = addition.o division.o main.o multiplication.o subtraction.o
all: $(OBJS) 
	g++ -g -o all $(OBJS) 

main.o: main.cpp
	g++ -g -o main.o -c main.cpp

addition.o: addition.cpp
	g++ -g -o addition.o -c addition.cpp

division.o: division.cpp 
	g++ -g -c  division.cpp -o division.o

multiplication.o: multiplication.cpp 
	g++ -g -o multiplication.o -c multiplication.cpp

subtraction.o: subtraction.cpp 
	g++ -g -o subtraction.o -c subtraction.cpp 
	
clean:
	rm -f *.o all
