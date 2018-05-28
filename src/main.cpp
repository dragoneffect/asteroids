#include "../include/const.h"
#include "../include/global.h"
#include "../include/menu.h"
//#include "../include/Model.h"
#include "../include/Asteroids.h"
#include "../include/Draw.h"
#include "../include/Ship.h"
#include "../include/assistant.h"
#include "../include/bullet.h"
#include "../include/interface.h"

bool is_it_the_end(Ship ship1, Ship ship2, long long int people) {
  if (ship1.destroyed && ship2.destroyed) {
    return true;
  }
  if (people < min_survivors) {
    return true;
  }
  return false;
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

  srand(time(NULL));
  Asteroid asteroid((float)rand() / RAND_MAX * 800, 0, "asteroid.png");

  bool menu_running = true;

  Clock clock;
  float restarting_time = 0;
  float red_time = -1;
  bool ability_red = false;
  bool ability_red_use = false;
  sf::Draw draw_obj;

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
      cout << restarting_time << "\n";
      ability_red = true;
      restarting_time = 0;

      if (red_time < 5) {
        red_time = 5;
      }
      cout << red_time << "\n";
    }

    while (window.pollEvent(event)) {
      //открываем меню по нажатию Esc
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
          menu_running = false;
          menu(window, menu_running);
          break;
        case sf::Keyboard::Space:
          if (ability_red) {
            ability_red_use = true;
            ability_red = false;
          }
          break;
          default: break;
          // case sf::Keyboard::Return:
        }
      }
    }

    window.clear();
    window.draw(map.model_sprite);
    window.setVerticalSyncEnabled(true);
    interface(window, ship, ship_2, count, earthlings, survived, red_time);
    if (is_it_the_end(ship, ship_2, earthlings)) {
      sf::Text text;
      sf::Font font;
      std::stringstream st;
      if (!font.loadFromFile("font.ttf")) {
        return -1;
      }
      text.setFont(font);
      st << "\tgame over";
      text.setString(st.str());
      text.setCharacterSize(30);
      text.setPosition(270, 270);
      window.draw(text);
    }

    else {
      survived += 100000;
      earthlings -= 100000;
      asteroid.update();
      if (asteroid.y() >= windowHeight) {
        earthlings -= 100000000;
      }
      if (asteroid.destroyed) {
        asteroid.model_sprite.setPosition((float)rand() / RAND_MAX * 600, 0);
        asteroid.destroyed = false;
      }
      if (!ship.destroyed) {
        ship.update();
        Collision(ship, asteroid, count);
      }
      draw_obj.Draw_object(window, bullet_3.destroyed, bullet_3.model_sprite);
      bullet_3.update();
      bullet_3.update();
      draw_obj.Bullet_position(ship.x() + ship_blue_width, ship.y(), bullet_3,
                               ship.destroyed);
      Collision(bullet_3, asteroid, count);
      if (!ship_2.destroyed) {
        ship_2.update();
        Collision(ship_2, asteroid, count);
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
            draw_obj.Bullet_position(assist.x() + ship_assist_width, assist.y(),
                                     bullet, assist.destroyed);
          } else
            ability_red_use = false;
        }
      }
      draw_obj.Draw_object(window, bullet_2.destroyed, bullet_2.model_sprite);
      bullet_2.update();
      bullet_2.update();
      bullet_2.update();
      draw_obj.Bullet_position(ship_2.x() + ship_red_width, ship_2.y(),
                               bullet_2, ship_2.destroyed);
      Collision(bullet_2, asteroid, count);
      draw_obj.Draw_object(window, ship.destroyed, ship.model_sprite);
      draw_obj.Draw_object(window, ship_2.destroyed, ship_2.model_sprite);
      draw_obj.Draw_object(window, asteroid.destroyed, asteroid.model_sprite);
    }
    //отрисовка окна
    window.display();
  }

  return 0;
}
