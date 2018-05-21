#ifndef SHIP_H
#define SHIP_H

#include "Model.h"

class Ship : public Model {
public:
  Vector2f velocity;
  int ship_health = 100;
  string ship_image;
  Keyboard::Key move_left, move_right;
  bool destroyed = false; //определяет, разрушен ли корабль или нет

  Ship(float X, float Y, string ship_image, Keyboard::Key _move_left,
       Keyboard::Key _move_right)
      : Model(ship_image) {
    model_sprite.setPosition(X, Y);
    move_left = _move_left;
    move_right = _move_right;
  }
  void update() {
    model_sprite.move(velocity);
    //если нажата только клавиша Left и корабль не уехал за границу, двигаемся
    //влево
    if (Keyboard::isKeyPressed(move_left) &&
        !Keyboard::isKeyPressed(move_right) && x() > 0)
      velocity.x = -ship_velocity;
    //аналогично здесь
    else if (Keyboard::isKeyPressed(move_right) &&
             !Keyboard::isKeyPressed(move_left) && x() < 764)
      velocity.x = ship_velocity;
    //если ничего не нажато, корабль не двигается
    else
      velocity.x = 0;
  }
  //вычисляем позицию
  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
};
#endif
