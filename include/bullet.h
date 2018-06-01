#ifndef BULLET_H
#define BULLET_H

#include "Model.h"
const float bullet_velocity = 5.f;

class Bullet : public Model {
public:
  Vector2f velocity;
  string bullet_image;
  bool destroyed = false;
  bool half = false;

  Bullet(float X, float Y, string bullet_image) : Model(bullet_image) {
    model_sprite.setPosition(X, Y);
  }

  void update() {
    model_sprite.move(velocity);
    velocity.y = -bullet_velocity;

    if (y() < 0) {
      destroyed = true;
    } else
      destroyed = false;
    if (y() <= 300) {
      half = true;
    }
  }

  void draw(sf::RenderWindow &window) { window.draw(model_sprite); }

  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
  float left() { return x() - model_texture.getSize().x / 2; }
  float right() { return x() + model_texture.getSize().x / 2; }
  float top() { return y() - model_texture.getSize().y / 2; }
  float bottom() { return y() + model_texture.getSize().y / 2; }
};

#endif
