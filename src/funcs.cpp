#include "../include/global.h"
#include "../include/Asteroids.h"
#include "../include/Ship.h"
#include "../include/const.h"

bool is_it_the_end(bool destroyed1, bool destroyed2, long long int people,
                   long long int survivors) {
  if (destroyed1 && destroyed2) {
    return true;
  }
  if (people < min_survivors) {
    return true;
  }
  return false;
}

bool ship_ability(bool start_ability, int &health1, int &health2,
                  float &ability_time) {
  if (start_ability && health1) {
    if (health1 != 3) {
      health1++;
    }
    if (health2 && health2 < 3) {
        health2++;
    }
    ability_time = 0;
    start_ability = false;
  }
  return start_ability;
}

void max_asteroids(long long int _survived, int &N) {
  long long int survied = _survived;
  if (survied < min_survivors) {
    N = 1;
  } else if (survied < max_survivors - 2 * min_survivors) {
    N = 2;
  } else
    N = 3;
}

void game_over(RenderWindow &window, int cause) {
  sf::Text text_over, text_cause;
  sf::Font font;
  std::stringstream st_over, st_cause;
  font.loadFromFile("etc/font.ttf");
  text_over.setFont(font);
  text_cause.setFont(font);
  st_over << "\tgame over";
  text_over.setString(st_over.str());
  text_over.setCharacterSize(30);
  text_over.setPosition(270, 270);
  text_over.setColor(sf::Color::Red);
  window.draw(text_over);
  if (cause == 0) {
    st_cause << "you are destroyed";
    text_cause.setPosition(225, 300);
  } else if (cause == 1) {
    st_cause << "people are dead";
    text_cause.setPosition(245, 300);

  } else {
    st_cause << "\tyou won!";
    text_cause.setPosition(286, 300);
  }
  text_cause.setString(st_cause.str());
  text_cause.setCharacterSize(30);
  text_cause.setColor(sf::Color::Red);
  window.draw(text_cause);
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
