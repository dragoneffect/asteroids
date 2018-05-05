
main: main.cpp
		g++ -Wall -g -DSFML_STATIC -I D:\prog\SFML\SFML-2.4.2\include -c main.cpp -o main.o
	g++ -L D:\prog\SFML\SFML-2.4.2\lib -o main main.o -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopenal32 -lfreetype -lopengl32 -ljpeg -lwinmm -lgdi32