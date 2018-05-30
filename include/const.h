#ifndef CONST_H
#define CONST_H

//константы размера окна
static const int windowWidth = 800, windowHeight = 600;
//минимальное количество выживших
static const long long int min_survivors = 2000000000;
//ширина кораблей/2
static float ship_blue_width = 36 / 2 - 4;
static float ship_red_width = 55 / 2 - 4;
static float ship_assist_width = 78 / 2 - 6;
//для начального положения кораблей на экране
static int start_x_blue = windowWidth / 2;
static int start_x_red = (windowWidth / 2) - 60;
static int start_ship_y = windowHeight - 80;
static int start_y_assist = windowHeight - 60;
static int start_x_assist = (windowWidth / 2) - 100;
static int firstToDraw = 0;

#endif
