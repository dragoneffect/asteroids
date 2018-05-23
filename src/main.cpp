#include "../include/global.h"
#include "../include/bullet.h"
#include "../include/const.h"
#include "../include/menu.h"
//#include "../include/Model.h"
#include "../include/Ship.h"
#include "../include/assistant.h"
//#include "../include/bullet.h"
#include "../include/Asteroids.h"
#include "../include/interface.h"

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

  Model map("background.png");
  //изначальная позиция кораблей
  Ship ship(start_x_blue, start_ship_y, "pl1.png", Keyboard::Left,
            Keyboard::Right);
  Ship ship_2(start_x_red, start_ship_y, "pl2.png", Keyboard::A, Keyboard::D);
  Assistant assist(start_x_assist, start_y_assist, "assistant.png",
                   Keyboard::Space);

  Bullet bullet(ship.x() + ship_blue_width, ship.y(), "bullet.png");
  Bullet bullet_2(ship_2.x() + ship_red_width, ship_2.y(), "bullet_red.png");
  srand(time(NULL));
  Asteroid asteroid((float)rand() / RAND_MAX * 600, 0, "asteroid.png");

  Bullet bullet_3(ship_2.x() + ship_red_width, ship_2.y(), "bullet_red.png");
  Bullet bullet_4(ship_2.x() + ship_red_width, ship_2.y(), "bullet_red.png");

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
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        menu_running = false;
        menu(window, menu_running);
      }
    }
    //  std::stringstream st;
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
        bullet.model_sprite.setPosition(ship.x() + ship_blue_width, ship.y());
        bullet.update();
      }

      if (bullet.half) {
        bullet_2.update();
      }
      if (bullet_2.destroyed) {
        bullet_2.model_sprite.setPosition(ship_2.x() + ship_red_width,
                                          ship_2.y());
      }
      if (asteroid.destroyed) {
        asteroid.model_sprite.setPosition((float)rand() / RAND_MAX * 600, 0);
      }
      if (bullet.half) {
        bullet_2.update();
      }
      if (bullet_2.destroyed) {
        bullet_2.model_sprite.setPosition(ship.x() + ship_blue_width, ship.y());
      }

      if (event.key.code == sf::Keyboard::Space) {
        if (ability_red) {
          ability_red_use = true;
          ability_red = false;
        } else {
          ability_red_use = false;
        }
      }

      if (ability_red_use) {
        if (red_time >= 0) {
          assist.update();
          window.draw(assist.model_sprite);
          red_time -= time;
          std::cout << red_time << "\n";
        }
        if (red_time <= 0)
          ability_red_use = false;
      }

      if (!ship.destroyed) {
        bullet.update();
        bullet.draw(window);
        if (bullet.destroyed) {
          bullet.model_sprite.setPosition(ship.x() + ship_blue_width, ship.y());
        }
        if (bullet.half) {
          bullet_2.update();
          bullet_2.draw(window);
        }
        if (bullet_2.destroyed) {
          bullet_2.model_sprite.setPosition(ship.x() + ship_blue_width,
                                            ship.y());
        }
      }
      if (!ship_2.destroyed) {
        bullet_3.update();
        bullet_3.draw(window);
        if (bullet_3.destroyed) {
          bullet_3.model_sprite.setPosition(ship_2.x() + ship_red_width,
                                            ship_2.y());
        }
        if (bullet_3.half) {
          bullet_4.update();
          bullet_4.draw(window);
        }
        if (bullet_4.destroyed) {
          bullet_4.model_sprite.setPosition(ship_2.x() + ship_red_width,
                                            ship_2.y());
        }
      }
    }

    bullet.draw(window);
    bullet_2.draw(window);

    interface(window, ship, ship_2, count);

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
