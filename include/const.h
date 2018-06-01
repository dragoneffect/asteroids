#ifndef CONST_H
#define CONST_H

//константы размера окна
static const int windowWidth = 800, windowHeight = 600;
//минимальное количество выживших
static const long long int min_survivors = 1000000000;
//достаточное количество выживших
static const long long int max_survivors = 8000000000;
//ширина кораблей
static float shipBlueW = 36;
static float shipRedW = 55;
//центры кораблей
static float ship_blue_width = 36 / 2 - 4;
static float ship_red_width = 55 / 2 - 4;
static float ship_assist_width = 38 / 2 - 4;
//для начального положения кораблей на экране
static int start_x_blue = windowWidth / 2;
static int start_x_red = (windowWidth / 2) - 60;
static int start_ship_y = windowHeight - 80;
static int start_y_assist = windowHeight - 85;
static int start_x_assist = (windowWidth / 2) - 100;
//время перезарядки и длительности способностей
static float red_restart = 10;
static float red_running = 5;

#endif
