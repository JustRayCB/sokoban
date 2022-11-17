COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g

main: main.cpp player.o rectangle.o gameObject.o board.o wall.o box.o
	$(COMPILER) -o main main.cpp player.o rectangle.o gameObject.o board.o wall.o box.o $(FLAGS)

rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)

player.o:  player.cpp player.hpp
	$(COMPILER) -c player.cpp $(FLAGS)

gameObject.o: gameObject.cpp gameObject.hpp
	$(COMPILER) -c gameObject.cpp $(FLAGS)

board.o: board.cpp board.hpp
	$(COMPILER) -c board.cpp $(FLAGS)

wall.o: wall.cpp wall.hpp
	$(COMPILER) -c wall.cpp $(FLAGS)

box.o: box.cpp box.hpp
	$(COMPILER) -c box.cpp $(FLAGS)
	


clear:
	rm *.o
	rm main

