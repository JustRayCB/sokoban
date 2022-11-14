COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g

main: main.cpp player.o rectangle.o
	$(COMPILER) -o main main.cpp player.o rectangle.o $(FLAGS)

rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)

player.o:  player.cpp player.hpp
	$(COMPILER) -c player.cpp $(FLAGS)

clear:
	rm *.o
	rm main

