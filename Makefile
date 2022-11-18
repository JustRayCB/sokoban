COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g

main: main.cpp player.o rectangle.o gameObject.o board.o wall.o box.o target.o
	$(COMPILER) -o main main.cpp player.o rectangle.o gameObject.o board.o wall.o box.o target.o $(FLAGS)

board.o: board.cpp board.hpp gameObject.o player.o wall.o box.o
	$(COMPILER) -c board.cpp  $(FLAGS)

gameObject.o: gameObject.cpp gameObject.hpp player.o
	$(COMPILER) -c gameObject.cpp  $(FLAGS)

player.o:  player.cpp player.hpp rectangle.o
	$(COMPILER) -c player.cpp $(FLAGS)

wall.o: wall.cpp wall.hpp rectangle.o
	$(COMPILER) -c wall.cpp $(FLAGS)

box.o: box.cpp box.hpp rectangle.o
	$(COMPILER) -c box.cpp $(FLAGS)
	
rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)

target.o: target.cpp target.hpp
	$(COMPILER) -c target.cpp $(FLAGS)

clear:
	rm *.o
	rm main

