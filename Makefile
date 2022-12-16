COMPILER = g++
FLAGS = -O2 -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g
#-fsanitize=undefined,leak,address -g 
main: main.cpp display.o controller.o rectangle.o gameObject.o board.o 
	$(COMPILER) -o main main.cpp display.o rectangle.o gameObject.o board.o controller.o $(FLAGS)

display.o: display.cpp display.hpp board.o
	$(COMPILER) -c display.cpp  $(FLAGS)

controller.o: controller.cpp controller.hpp board.o
	$(COMPILER) -c controller.cpp  $(FLAGS)


board.o: board.cpp board.hpp gameObject.o rectangle.o
	$(COMPILER) -c board.cpp  $(FLAGS)

gameObject.o: gameObject.cpp gameObject.hpp rectangle.o
	$(COMPILER) -c gameObject.cpp  $(FLAGS)

rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)


clean:
	rm *.o
	rm main
	ls

