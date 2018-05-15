#include <iostream>
#include <sstream>
#include <cstdlib>
#include "global.h"
//#include "Game_window.h"


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
