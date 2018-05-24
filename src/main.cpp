#include "../include/const.h"
#include "../include/global.h"
#include "../include/bullet.h"
#include "../include/menu.h"
//#include "../include/Model.h"
#include "../include/Ship.h"
#include "../include/assistant.h"
//#include "../include/bullet.h"
#include "../include/Asteroids.h"
#include "../include/interface.h"

bool is_it_the_end(RenderWindow &window, Ship ship1, Ship ship2,
                   long long int people) {
  sf::Text text;
  sf::Font font;
  std::stringstream st;
  if (!font.loadFromFile("font.ttf")) {
    return -1;
  }
  text.setFont(font);

  if (ship1.destroyed && ship2.destroyed) {
    st << "\t\t\t\tgame over"
       << "\n"
       << "both of your ships destroyed";
    text.setString(st.str());
    text.setCharacterSize(30);
    text.setPosition(170, 270);
    window.draw(text);
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

template <class T1, class T2> bool isIntersecting(T1 &object, T2 &asteroid) {
  return object.right() >= asteroid.left() &&
         object.left() <= asteroid.right() &&
         object.bottom() >= asteroid.top() && object.top() <= asteroid.bottom();
}

void Collision(Ship &ship, Asteroid &asteroid, int &count) {
  //если столкновения не было, ничего не произойдет
  if (!isIntersecting(ship, asteroid)) {
    return;
  }
  //иначе разрушаем астероид, отнимаем одну жизнь у корабля
  asteroid.destroyed = true;
  ship.ship_health--;
  count += 10;
}

void Collision(Bullet &bullet, Asteroid &asteroid, int &count) {
  if (!isIntersecting(bullet, asteroid)) {
    return;
  }
  asteroid.destroyed = true;
  bullet.destroyed = true;
  count += 10;
}

int main() {
  //счет
  int count = 0;
  //изначальное количество землян.
  long long int earthlings = 10000000000;
  long long int survived = 0;

  Model map("background.png");
  //изначальная позиция кораблей
  Ship ship(start_x_blue, start_ship_y, "pl1.png", Keyboard::Left,
            Keyboard::Right);
  Ship ship_2(start_x_red, start_ship_y, "pl2.png", Keyboard::A, Keyboard::D);
  Assistant assist(start_x_assist, start_y_assist, "assistant.png",
                   Keyboard::Space);

  Bullet bullet(assist.x() + ship_assist_width, assist.y(), "bullet_green.png");
  Bullet bullet_2(ship_2.x() + ship_red_width, ship_2.y(), "bullet_red.png");
  Bullet bullet_3(ship.x() + ship_blue_width, ship.y(), "bullet.png");

  vector<Bullet> bullets_red, bullets_blue;
  for (int i = 0; i < 2; i++) {
    bullets_red.push_back(bullet_2);
    //  bullets_red.emplace_back((ship_2.x() + ship_red_width), (ship_2.y() *
    //  i), "bullet_red.png");
    bullets_blue.push_back(bullet_3);
  }

  srand(time(NULL));
  Asteroid asteroid((float)rand() / RAND_MAX * 600, 0, "asteroid.png");

  bool menu_running = true;

  Clock clock;
  float restarting_time = 0;
  float red_time = -1;
  bool ability_red = false;
  bool ability_red_use = false;

  //открытие окна
  sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids",
                          sf::Style::Close);
  //программа работает, пока окно открыто
  while (window.isOpen()) {
    sf::Event event;

    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    restarting_time += time;

    if (restarting_time > 10 && red_time != 5) {
      std::cout << restarting_time << "\n";
      ability_red = true;
      restarting_time = 0;

      if (red_time <= 5) {
        red_time = 5;
      }
      std::cout << red_time << "\n";
    }

    while (window.pollEvent(event)) {
      //открываем меню по нажатию Esc
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          menu_running = false;
          menu(window, menu_running);
        } else if (event.key.code == sf::Keyboard::Space) {
          if (ability_red) {
            ability_red_use = true;
            ability_red = false;
          } else {
            ability_red_use = false;
          }
        }
      }
    }

    window.clear();
    window.draw(map.model_sprite);
    window.setVerticalSyncEnabled(true);
    interface(window, ship, ship_2, count, earthlings, survived, red_time);
    // bool fl = true;

    if (is_it_the_end(window, ship, ship_2, earthlings)) {
      survived += 100000;
      earthlings -= 100000;
      asteroid.update();
      if (asteroid.y() >= 599) {
        earthlings -= 100000000;
      }
      if (asteroid.destroyed) {
        asteroid.model_sprite.setPosition((float)rand() / RAND_MAX * 600, 0);
        asteroid.destroyed = false;
      }
      if (!ship.destroyed) {
        ship.update();
        //    Collision(ship, asteroid, count);
        for (auto &bullet : bullets_blue) {
          bullet.update();
          bullet.update();
          bullet.draw(window);
          if (bullet.destroyed) {
            bullet.model_sprite.setPosition(ship.x() + ship_blue_width,
                                            ship.y());
            bullet.destroyed = false;
          }
          Collision(bullet, asteroid, count);
        }
      }
      if (!ship_2.destroyed) {
        ship_2.update();
        Collision(ship_2, asteroid, count);
        for (auto &bullet : bullets_red) {
          bullet.update();
          bullet.update();
          bullet.update();
          bullet.draw(window);
          if (bullet.destroyed) {
            bullet.model_sprite.setPosition(ship_2.x() + ship_red_width,
                                            ship_2.y());
            bullet.destroyed = false;
          }
          Collision(bullet, asteroid, count);
        }
        if (ability_red_use) {
          if (red_time >= 0) {
            assist.update();
            bullet.update();
            bullet.update();
            bullet.update();
            bullet.draw(window);
            window.draw(assist.model_sprite);
            Collision(bullet, asteroid, count);
            red_time -= time;
            if (bullet.destroyed) {
              bullet.model_sprite.setPosition(assist.x() + ship_assist_width,
                                              assist.y());
              bullet.destroyed = false;
            }
          }
          if (red_time <= 0)
            ability_red_use = false;
        }
      }
    }

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

    //отрисовка окна
    window.display();
  }

  return 0;
}
