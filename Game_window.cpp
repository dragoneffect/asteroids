#include <SFML/Graphics.hpp>
#include <iostream>
#include "model.h"

using namespace std;
using namespace sf;

bool is_it_the_end(Ship ship1, Ship_2 ship2, long long int people) {
  if (ship1.destroyed || ship2.destroyed) {
    return false;
  }
  if (people < 2000000000) {
    return false;
  }
  return true;
}

void Window(){
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
Ship ship_2((windowWidth / 2) - 50, windowHeight - 80, Keyboard::A, Keyboard::D);
//открытие окна
sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close);
std::stringstream st;

window.clear();
window.draw(map.model_sprite);
window.setVerticalSyncEnabled(true);
bool fl = true;

if (is_it_the_end(ship, ship_2, earthlings)) {
  ship.update();
  ship_2.update();
  if(ship.x() > ship_2.x() && ship.x() < ship_2.x() + 55)
      fl = false;
  else
    if(ship.x() < ship_2.x() && ship.x() > ship_2.x() - 36) fl = false;
            else fl = true;
}

//вывод счета на экран
st << count;
text.setString(st.str());

if(fl) firstToDraw = 1 - firstToDraw;

if(firstToDraw){
    window.draw(ship_2.ship_sprite);
    window.draw(ship.model_sprite);
}
else{
    window.draw(ship.model_sprite);
    window.draw(ship_2.ship_sprite);
}

window.draw(text);

//отрисовка окна
window.display();
}

//ДВИЖИЕНИЕ
void update() {
  model_sprite.move(velocity);
  //если нажата только клавиша Left и корабль не уехал за границу, двигаемся влево
  if(Keyboard::isKeyPressed(move_left) && !Keyboard::isKeyPressed(move_right) && x() > 0)
      velocity.x = -ship_velocity;
  //аналогично здесь
  else if (Keyboard::isKeyPressed(move_right) && !Keyboard::isKeyPressed(move_left) && x() < 764)
      velocity.x = ship_velocity;
  //если ничего не нажато, корабль не двигается
  else
    velocity.x = 0;
}
