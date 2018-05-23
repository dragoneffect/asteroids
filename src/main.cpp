#include "../include/global.h"
#include "../include/menu.h"
#include "../include/bullet.h"
//#include "../include/Model.h"
#include "../include/Ship.h"
#include "../include/Asteroids.h"


bool is_it_the_end(Ship ship1, Ship ship2, long long int people) {
  if (ship1.destroyed && ship2.destroyed) {
    return false;
  }
  if (people < min_survivors) {
    return false;
  }
  return true;
}

bool first_to_draw(Ship ship, Ship ship_2) {
  if (ship.x() > ship_2.x() && ship.x() < ship_2.x() + 55)
    return false;
  else if (ship.x() < ship_2.x() && ship.x() > ship_2.x() - 36)
    return false;
  else
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
  Model map("background.png");
  //изначальная позиция корабля
  Ship ship(start_x_blue, start_ship_y, "pl1.png", Keyboard::Left,
            Keyboard::Right);
  Ship ship_2(start_x_red, start_ship_y, "pl2.png", Keyboard::A, Keyboard::D);

  Bullet bullet(ship.x() + ship_blue_width, ship.y(), "bullet.png");
  Bullet bullet_2(ship_2.x() + ship_red_width, ship_2.y(), "bullet_red.png");
  srand(time(NULL));
  Asteroid asteroid((float)rand() / RAND_MAX * 600, 0, "asteroid.png");

  bool menu_running = true;
  //открытие окна
  sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids",
                          sf::Style::Close);
  //программа работает, пока окно открыто
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      //открываем меню по нажатию Esc
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        menu_running = false;
        menu(window, menu_running);
      }
    }
    std::stringstream st;
    window.clear();
    window.draw(map.model_sprite);
    window.setVerticalSyncEnabled(true);
    // bool fl = true;

    if (is_it_the_end(ship, ship_2, earthlings)) {
      ship.update();
      ship_2.update();
      bullet.update();
      bullet_2.update();
      asteroid.update();
      if (bullet.destroyed) {
        bullet.model_sprite.setPosition(ship.x() + ship_blue_width,ship.y());
      }
      if (bullet.half)
        bullet_2.update();
      if (bullet_2.destroyed) {
        bullet_2.model_sprite.setPosition(ship_2.x() + ship_red_width, ship_2.y());
      }
      if(asteroid.destroyed){
         asteroid.model_sprite.setPosition((float)rand() / RAND_MAX * 600, 0);
      }
    }
    //вывод счета на экран
    st << count;
    text.setString(st.str());

    bullet.draw(window);
    bullet_2.draw(window);


    if (first_to_draw(ship, ship_2))
      firstToDraw = 1 - firstToDraw;

    if (firstToDraw) {
      window.draw(ship_2.model_sprite);
      window.draw(ship.model_sprite);
    } else {
      window.draw(ship.model_sprite);
      window.draw(ship_2.model_sprite);
    }
    window.draw(asteroid.model_sprite);
    window.draw(text);

    //отрисовка окна
    window.display();
  }
  return 0;
}
