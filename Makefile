COMPILER = g++
FLAGS = -std=c++20 -Wall -Wextra -pedantic -fsanitize=address `fltk-config --ldflags` -g
# FLAGS += $(shell fltk-config --cxxflags)
# FLAGS  += $(shell fltk-config --ldflags)

#-fsanitize=undefined,leak,address -g 
main: main.cpp display.o controller.o rectangle.o gameObject.o board.o text.o levelEditor.o grid.o mainWindow.o
	$(COMPILER) -o main main.cpp display.o rectangle.o gameObject.o board.o controller.o text.o levelEditor.o grid.o mainWindow.o $(FLAGS)

mainWindow.o: mainWindow.cpp mainWindow.hpp board.o display.o controller.o levelEditor.o
	$(COMPILER) -c mainWindow.cpp  $(FLAGS)


display.o: display.cpp display.hpp board.o
	$(COMPILER) -c display.cpp  $(FLAGS)

controller.o: controller.cpp controller.hpp board.o
	$(COMPILER) -c controller.cpp  $(FLAGS)

levelEditor.o: levelEditor.cpp levelEditor.hpp board.o grid.o
	$(COMPILER) -c levelEditor.cpp $(FLAGS)

board.o: board.cpp board.hpp gameObject.o rectangle.o
	$(COMPILER) -c board.cpp  $(FLAGS)

gameObject.o: gameObject.cpp gameObject.hpp rectangle.o
	$(COMPILER) -c gameObject.cpp  $(FLAGS)

rectangle.o: rectangle.cpp rectangle.hpp 
	$(COMPILER) -c rectangle.cpp $(FLAGS)

text.o: text.cpp text.hpp
	$(COMPILER) -c text.cpp $(FLAGS)

grid.o: grid.cpp grid.hpp
	$(COMPILER) -c grid.cpp $(FLAGS)

clean:
	rm *.o
	rm main

