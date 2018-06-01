#ifndef SHIP_H
#define SHIP_H

#include "Model.h"

const float ship_velocity = 6.f;

class Ship : public Model {
public:
  Vector2f velocity;
  int ship_health = 3;
  string ship_image;
  Keyboard::Key move_left, move_right;
  float ship_width;
  bool destroyed = false; //определяет, разрушен ли корабль или нет

  Ship(float X, float Y, string ship_image, Keyboard::Key _move_left,
       Keyboard::Key _move_right, float _ship_width)
      : Model(ship_image) {
    model_sprite.setPosition(X, Y);
    move_left = _move_left;
    move_right = _move_right;
    ship_width = _ship_width;
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
             !Keyboard::isKeyPressed(move_left) && x() < 800 - ship_width)
      velocity.x = ship_velocity;
    //если ничего не нажато, корабль не двигается
    else
      velocity.x = 0;
    if (ship_health == 0) {
      destroyed = true;
    }
  }
  //вычисляем позицию
  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
  float left() { return x() - model_texture.getSize().x / 2; }
  float right() { return x() + model_texture.getSize().x / 2; }
  float top() { return y() - model_texture.getSize().y / 2; }
  float bottom() { return y() + model_texture.getSize().y / 2; }
};

#endif
