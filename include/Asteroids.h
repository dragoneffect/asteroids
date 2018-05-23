#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "bullet.h"

const float asteroid_velocity = 6.f;

class Asteroid : public Bullet {
public:
  Asteroid(float X, float Y, string asteroid_image)
      : Bullet(X, Y, asteroid_image) {}

  void update() {
      destroyed = false;
    if (model_sprite.getPosition().y < 600 && (!destroyed)) {
      model_sprite.move(velocity);
      velocity.y = asteroid_velocity;
    }
    if(y() == 600) destroyed = true;
  }
  float x() { return model_sprite.getPosition().x; }
  float y() { return model_sprite.getPosition().y; }
  float left() { return x() - 20; }
  float right() { return x() + 20; }
  float top() { return y() - 52; }
  float bottom() { return y() + 52; }
};
#endif
