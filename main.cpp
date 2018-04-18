#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//константа скорости корабля
const float ship_velocity = 7.f;

struct Ship {
  Vector2f velocity;
  Image ship_image;
  Texture ship_texture;
  Sprite ship_sprite;

  Ship(float X, float Y) {
    ship_image.loadFromFile("images/pl1.png");
    ship_texture.loadFromImage(ship_image);
    ship_sprite.setTexture(ship_texture);
    ship_sprite.setPosition(X, Y);

    //определяет, разрушен ли корабль или нет
    // bool destroyed = false;
  }

  void update() {
    ship_sprite.move(velocity);
    //если нажата А и корабль не уехал за границу, двигаемся влево
    if (Keyboard::isKeyPressed(sf::Keyboard::A) && x() > 0) {
      velocity.x = -ship_velocity;
    }
    //аналогично здесь
    else if (Keyboard::isKeyPressed(sf::Keyboard::D) && x() < 750) {
      velocity.x = ship_velocity;
    }
    //если ничего не нажато, корабль не двигается
    else {
      velocity.x = 0;
    }

  }

  //вычисляем позицию
  float x() { return ship_sprite.getPosition().x; }
};

int main() {
  //изначальная позиция корабля
  Ship ship(windowWidth / 2, windowHeight - 100);

  //открытие окна
  sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids",
                          sf::Style::Default);

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

    window.clear(Color::Black);

    window.setVerticalSyncEnabled(true);

    ship.update();

    window.draw(ship.ship_sprite);

    //отрисовка окна
    window.display();
  }

  return 0;
}
