COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic `fltk-config --ldflags` -g
#FLAGS += $(shell fltk-config --cxxflags)
#FLAGS  += $(shell fltk-config --ldflags)

#-fsanitize=undefined,leak,address -g 
main: main.cpp display.o controller.o rectangle.o gameObject.o board.o  levelEditor.o
	$(COMPILER) -o main main.cpp display.o rectangle.o gameObject.o board.o controller.o levelEditor.o $(FLAGS)

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

levelEditor.o: levelEditor.cpp levelEditor.hpp
	$(COMPILER) -c levelEditor.cpp $(FLAGS)

clean:
	rm *.o
	rm main

