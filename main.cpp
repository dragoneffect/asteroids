//#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Window.h"

//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//константа скорости корабля
const float ship_velocity = 6.f;
//изначальное количество землян.
const long long int earthlings = 10000000000;

int firstToDraw = 0;

using namespace std;
using namespace sf;

int main() {
  //программа работает, пока окно открыто
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      //закрываем окно (в т.ч. по нажатию Escape)
      if (event.type == sf::Event::Closed ||
          (event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape)) {
        window.close();
      }
    }
    Window();
}
  return 0;
}
