OBJS = addition.o division.o main.o multiplication.o subtraction.o
CPP = g++
FLAGS = -g
RM = rm -f 
all: $(OBJS) 
	$(CPP) $(FLAGS) -o all $(OBJS) 

main.o: main.cpp
	$(CPP) $(FLAGS) -o main.o -c main.cpp

addition.o: addition.cpp
	$(CPP) $(FLAGS) -o addition.o -c addition.cpp

division.o: division.cpp 
	$(CPP) $(FLAGS) -c  division.cpp -o division.o

multiplication.o: multiplication.cpp 
	$(CPP) $(FLAGS) -o multiplication.o -c multiplication.cpp

subtraction.o: subtraction.cpp 
	$(CPP) $(FLAGS) -o subtraction.o -c subtraction.cpp 
	
clean:
	$(RM) $(OBJS) all
