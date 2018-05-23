
CC=g++

OBJ = $(CC) -Wall -g -DSFML_STATIC -I SFML\include -c $< -o $@ $(CXXFLAGS)

CXXFLAGS= -L SFML\lib -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopenal32 -lfreetype -lopengl32 -ljpeg -lwinmm -lgdi32

default: asteroids

asteroids: build/main.o build/menu.o 
	$(CC) $^ -o $@ $(CXXFLAGS) 

build/main.o: src/main.cpp
	mkdir -p build
	 $(OBJ) -std=c++11

build/menu.o: src/menu.cpp
	$(OBJ) 

clean:
	rm -f build/*.o
	rm build
