# A starter makefile for CSE 100 P2

#use g++ for everything
CC= g++ 
CXX= g++

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall -std=c++11

#include debugging symbols in executable
LDFLAGS= -g	

default: main tester_TST  tester_Autocomplete 

main: main.o 
	g++ -o main main.o
tester_TST: tester_TST.o 
	g++ -o tester_TST tester_TST.o
tester_Autocomplete:  tester_Autocomplete.o
	g++ -o tester_Autocomplete tester_Autocomplete.o
main.o: main.cpp Autocomplete.hpp TST.hpp TSTNode.hpp
Autocomplete.o: Autocomplete.hpp
TST.o: TST.hpp TSTNode.hpp
tester_TST.o: Autocomplete.hpp TST.hpp TSTNode.hpp
tester_Autocomplete.o : Autocomplete.hpp TST.hpp TSTNode.hpp
clean:
	$(RM) main *.o 
