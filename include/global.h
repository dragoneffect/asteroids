#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//константа скорости корабля
float ship_velocity = 6.f;
//изначальное количество землян.
const long long int earthlings = 10000000000;

int firstToDraw = 0;

using namespace std;
using namespace sf;

#include "Model.h"
#include "Ship.h"
#endif
