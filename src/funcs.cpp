#include "../include/global.h"
#include "../include/const.h"
#include "../include/Ship.h"
#include "../include/Asteroids.h"

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
