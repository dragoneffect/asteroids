
main: main.o
		g++ -L SFML\lib -o main main.o -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopenal32 -lfreetype -lopengl32 -ljpeg -lwinmm -lgdi32
main.o: main.cpp Game_window.h Window.o
		g++ -Wall -g -DSFML_STATIC -I SFML\include -c main.cpp
Window.o: Game_window.cpp model.h
		g++ -Wall -c Game_window.cpp 
		