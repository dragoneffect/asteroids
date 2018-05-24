#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "Model.h"

class Assistant : public Model {
public:
  Vector2f velocity;
  string ship_image;
  bool destroyed = false; //определяет, разрушен ли корабль или нет
  bool direction = true;
  Keyboard::Key ability;

  Assistant(float X, float Y, string ship_image, Keyboard::Key _ability)
      : Model(ship_image) {
    model_sprite.setPosition(X, Y);
  ability = _ability;
  }
  void update() {
    model_sprite.move(velocity);
      if (x() < 750 && direction) {
      velocity.x = -ship_velocity;
      if (x() < 0)
        direction = false;
    }
    else if (x() < 0 || !direction) {
      velocity.x = ship_velocity;
      if (x() > 730)
        direction = true;
    }
  }
  //вычисляем позицию
  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
  float left() { return x() - model_texture.getSize().x/2; }
  float right() { return x() + model_texture.getSize().x/2; }
  float top() { return y() - model_texture.getSize().y/2; }
  float bottom() { return y() + model_texture.getSize().y/2; }
};
#endif
