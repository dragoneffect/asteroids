#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "bullet.h"

const float asteroid_velocity = 6.f;

class Asteroid : public Bullet {
public:
  Asteroid(float X, float Y, string asteroid_image)
      : Bullet(X, Y, asteroid_image) {}

  void update() {
    if (y() < windowHeight && !destroyed) {
      model_sprite.move(velocity);
      velocity.y = asteroid_velocity;
    }
    else destroyed = true;
  }
  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
  float left() { return x() - model_texture.getSize().x/2; }
  float right() { return x() + model_texture.getSize().x/2; }
  float top() { return y() - model_texture.getSize().y/2; }
  float bottom() { return y() + model_texture.getSize().y/2; }
};
#endif
