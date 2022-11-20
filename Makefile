COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g

main: main.cpp display.o controller.o rectangle.o gameObject.o newboard.o 
	$(COMPILER) -o main main.cpp display.o rectangle.o gameObject.o newboard.o controller.o $(FLAGS)

display.o: display.cpp display.hpp newboard.o
	$(COMPILER) -c display.cpp  $(FLAGS)

controller.o: controller.cpp controller.hpp newboard.o
	$(COMPILER) -c controller.cpp  $(FLAGS)


newboard.o: newboard.cpp board.hpp gameObject.o rectangle.o
	$(COMPILER) -c newboard.cpp  $(FLAGS)

gameObject.o: gameObject.cpp gameObject.hpp rectangle.o
	$(COMPILER) -c gameObject.cpp  $(FLAGS)

rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)


clear:
	rm *.o
	rm main

