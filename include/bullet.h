#ifndef BULLET_H
#define BULLET_H

const float bullet_velocity = 15.f;

class Bullet {
public:
  Vector2f velocity;
  Image bullet_image;
  Texture bullet_texture;
  Sprite bullet_sprite;
  bool destroyed = false;
  bool half = false;

  Bullet(float X, float Y) {
    bullet_image.loadFromFile("images/bullet.png");
    bullet_image.createMaskFromColor(Color(0, 0, 0));
    bullet_texture.loadFromImage(bullet_image);
    bullet_sprite.setTexture(bullet_texture);
    bullet_sprite.setPosition(X, Y);
  }

  void update() {
    bullet_sprite.move(velocity);
    velocity.y = -bullet_velocity;

    if (bullet_sprite.getPosition().y < 0) {
      destroyed = true;
    }
    else if (bullet_sprite.getPosition().y > 0) {
      destroyed = false;
    }
    if (bullet_sprite.getPosition().y <= 300) {
      half = true;
    }
  }

  void draw(sf::RenderWindow &window) {
    window.draw(bullet_sprite);
  }

  float y() { return bullet_sprite.getPosition().y; }
};

#endif
