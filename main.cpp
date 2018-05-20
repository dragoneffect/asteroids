#include "include/global.h"

bool is_it_the_end(Ship ship1, Ship ship2, long long int people) {
  if (ship1.destroyed && ship2.destroyed) {
    return false;
  }
  if (people < 2000000000) {
    return false;
  }
  return true;
}

bool first_to_draw(Ship ship, Ship ship_2) {
  if(ship.x() > ship_2.x() && ship.x() < ship_2.x() + 55)
     return false;
     else
       if(ship.x() < ship_2.x() && ship.x() > ship_2.x() - 36) return false;
           else return true;
}

int main() {
    int count = 0;
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
         return -1;
    }
    sf::Text text;
    text.setFont(font);
    Model map("background.png");
    //изначальная позиция корабля
    Ship ship(windowWidth / 2, windowHeight - 80, "pl1.png", Keyboard::Left, Keyboard::Right);
    Ship ship_2((windowWidth / 2) - 50, windowHeight - 80,"pl2.png", Keyboard::A, Keyboard::D);
    //открытие окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close);
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
    std::stringstream st;
    window.clear();
    window.draw(map.model_sprite);
    window.setVerticalSyncEnabled(true);
    //bool fl = true;

    if (is_it_the_end(ship, ship_2, earthlings)) {
      ship.update();
      ship_2.update();
    }
    //вывод счета на экран
    st << count;
    text.setString(st.str());

    if(first_to_draw(ship, ship_2)) firstToDraw = 1 - firstToDraw;

    if(firstToDraw){
        window.draw(ship_2.model_sprite);
        window.draw(ship.model_sprite);
    }
    else{
        window.draw(ship.model_sprite);
        window.draw(ship_2.model_sprite);
    }

    window.draw(text);

    //отрисовка окна
    window.display();
}
  return 0;
}
