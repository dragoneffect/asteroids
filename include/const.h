#ifndef CONST_H
#define CONST_H

//константы размера окна
const int windowWidth = 800, windowHeight = 600;
//минимальное количество выживших
const long long int min_survivors = 2000000000;
//ширина кораблей/2
float ship_blue_width = 36 / 2 - 4;
float ship_red_width = 55 / 2 - 4;
//для начального положения кораблей на экране
int start_x_blue = windowWidth / 2;
int start_x_red = (windowWidth / 2) - 60;
int start_ship_y = windowHeight - 80;
int start_y_assist = windowHeight - 60;
int start_x_assist = (windowWidth / 2) - 100;
int firstToDraw = 0;

#endif
