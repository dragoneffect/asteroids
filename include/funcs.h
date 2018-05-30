#ifndef FUNCS_H
#define FUNCS_H

#include "Ship.h"
#include "Asteroids.h"

bool is_it_the_end(Ship ship1, Ship ship2, long long int people);
bool first_to_draw(Ship ship, Ship ship_2);
template <class T1, class T2> bool isIntersecting(T1 &object, T2 &asteroid);
void Collision(Ship &ship, Asteroid &asteroid, int &count);
void Collision(Bullet &bullet, Asteroid &asteroid, int &count);

#endif
