#include "menu.h"

//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//константа скорости корабля
const float ship_velocity = 6.f;
//изначальное количество землян
const float earthlings = 10.000000000;


class Ship {
public: //чтобы потом преобразовать класс в родительский
  Vector2f velocity;
  Image ship_image;
  Texture ship_texture;
  Sprite ship_sprite;
  int ship_health = 100;
  bool destroyed = false; //определяет, разрушен ли корабль или нет

  Ship(float X, float Y) {
    ship_image.loadFromFile("images/pl1.png");
    ship_image.createMaskFromColor(Color(0, 0, 0));
    ship_texture.loadFromImage(ship_image);
    ship_sprite.setTexture(ship_texture);
    ship_sprite.setPosition(X, Y);
  }

  void update() {
    ship_sprite.move(velocity);
    //если нажата только клавиша Left и корабль не уехал за границу, двигаемся
    //влево
    if (Keyboard::isKeyPressed(Keyboard::Left) &&
        !Keyboard::isKeyPressed(Keyboard::Right) && x() > 0)
      velocity.x = -ship_velocity;
    //аналогично здесь
    else if (Keyboard::isKeyPressed(Keyboard::Right) &&
             !Keyboard::isKeyPressed(Keyboard::Left) && x() < 764)
      velocity.x = ship_velocity;
    //если ничего не нажато, корабль не двигается
    else
      velocity.x = 0;
  }

  //вычисляем позицию
  float x() { return ship_sprite.getPosition().x; }
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

    //если нажата A и корабль не уехал за границу, двигаемся влево
    if (Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !Keyboard::isKeyPressed(sf::Keyboard::D) && x() > 0) {
      velocity.x = -ship_velocity;
    }
    //аналогично здесь
    else if (Keyboard::isKeyPressed(sf::Keyboard::D) &&
             !Keyboard::isKeyPressed(sf::Keyboard::A) && x() < 745) {
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

bool is_it_the_end(Ship ship1, Ship_2 ship2, float people) {
  if (ship1.destroyed && ship2.destroyed) {
    return false;
  }
  if (people < 2.000000000) {
    return false;
  }
  return true;
}

int main() {
  int count = 0;
  Image map_image;
  map_image.loadFromFile("images/background.png");
  Texture map;
  map.loadFromImage(map_image);
  Sprite s_map;
  s_map.setTexture(map);

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

  bool is_running = true;

  //программа работает, пока окно открыто
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      //открываем меню по нажатию Esc
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        is_running = false;
        menu(window, is_running);
      }
    }

    std::stringstream st;

    window.clear();
    window.draw(s_map);
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
