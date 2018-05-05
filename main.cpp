#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//константа скорости корабля
const float ship_velocity = 6.f;
//изначальное количество землян
const long long int earthlings = 10000000000;

class Ship {
public: //чтобы потом преобразовать класс в родительский
  Vector2f velocity;
  Image ship_image;
  Texture ship_texture;
  Sprite ship_sprite;
  int ship_health = 100;

  Ship(float X, float Y) {
    ship_image.loadFromFile("images/pl1.png");
    ship_image.createMaskFromColor(Color(0, 0, 0));
    ship_texture.loadFromImage(ship_image);
    ship_sprite.setTexture(ship_texture);
    ship_sprite.setPosition(X, Y);
  }

  void update() {
    ship_sprite.move(velocity);
    //если нажата Left и корабль не уехал за границу, двигаемся влево
    if (Keyboard::isKeyPressed(sf::Keyboard::Left) && x() > 0) {
      velocity.x = -ship_velocity;
    }
    //аналогично здесь
    else if (Keyboard::isKeyPressed(sf::Keyboard::Right) && x() < 764) {
      velocity.x = ship_velocity;
    }
    //если ничего не нажато, корабль не двигается
    else {
      velocity.x = 0;
    }
  }

  //вычисляем позицию
  float x() { return ship_sprite.getPosition().x; }

  //определяет, разрушен ли корабль или нет
  bool destroyed = false;
};

class Ship_2 {
public:
  Vector2f velocity;
  Image ship_image;
  Texture ship_texture;
  Sprite ship_sprite;
  int ship_health = 100;

  Ship_2(float X, float Y) {
    ship_image.loadFromFile("images/pl2.png");
    ship_image.createMaskFromColor(Color(0, 0, 0));
    ship_texture.loadFromImage(ship_image);
    ship_sprite.setTexture(ship_texture);
    ship_sprite.setPosition(X, Y);
  }

  void update() {
    ship_sprite.move(velocity);

    /*присутствует баг при нажатием двух клавиш одновременно
    приоритет при движении влево, отсюда разное поведение
    в правой и левой границах экрана*/

    //если нажата Left и корабль не уехал за границу, двигаемся влево
    if (Keyboard::isKeyPressed(sf::Keyboard::A) && x() > 0) {
      velocity.x = -ship_velocity;
    }
    //аналогично здесь
    else if (Keyboard::isKeyPressed(sf::Keyboard::D) && x() < 745) {
      velocity.x = ship_velocity;
    }
    //если ничего не нажато, корабль не двигается
    else {
      velocity.x = 0;
    }
  }

  //вычисляем позицию
  float x() { return ship_sprite.getPosition().x; }

  //определяет, разрушен ли корабль или нет
  bool destroyed = false;
};

bool is_it_the_end(Ship ship1, Ship_2 ship2, long long int people) {
  if (ship1.destroyed && ship2.destroyed) {
    return false;
  }
  if (people < 2000000000) {
    return false;
  }
  return true;
}

int main() {

  int count = 0;

  sf::Font font;
  if (!font.loadFromFile("font.ttf")) {
    return -1;
  }
  sf::Text text;
  text.setFont(font);

  //изначальная позиция корабля
  Ship ship(windowWidth / 2, windowHeight - 80);
  Ship_2 ship_2((windowWidth / 2) - 50, windowHeight - 80);

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

    std::stringstream st;

    window.clear(Color::Black);

    window.setVerticalSyncEnabled(true);

    if (is_it_the_end(ship, ship_2, earthlings)) {
      ship.update();
      ship_2.update();
    }

    //вывод счета на экран
    st << count;
    text.setString(st.str());

    window.draw(ship_2.ship_sprite);
    window.draw(ship.ship_sprite);
    window.draw(text);

    //отрисовка окна
    window.display();
  }

  return 0;
}
