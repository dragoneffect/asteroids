#ifndef FUNCS_H
#define FUNCS_H

#include "Asteroids.h"
#include "Ship.h"

bool is_it_the_end(bool destroyed1, bool destroyed2, long long int people,
                   long long int survivors);
void game_over(RenderWindow &window, int cause);
bool ship_ability(bool start_ability, int &health1, int &health2,
                  float &ability_time);
void max_asteroids(long long int _survived, int &N);
template <class T1, class T2> bool isIntersecting(T1 &object, T2 &asteroid);
void Collision(Ship &ship, Asteroid &asteroid, int &count);
void Collision(Bullet &bullet, Asteroid &asteroid, int &count);

#endif
