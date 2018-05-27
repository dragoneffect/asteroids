#ifndef DRAW_H
#define DRAW_H

namespace sf {
class Draw {
public:
  bool destroyed;
  Sprite object_sprite;
  float X, Y;
  void Draw_object(sf::RenderWindow &window, bool _destroyed,
                   Sprite _object_sprite) {
    destroyed = _destroyed;
    object_sprite = _object_sprite;
    if (!destroyed)
      window.draw(object_sprite);
  }
  void Bullet_position(float _X, float _Y, Bullet &bullet, bool _destroyed) {
    X = _X; Y = _Y;
    destroyed = _destroyed;
    if (bullet.destroyed && !destroyed) {
      bullet.model_sprite.setPosition(X, Y);
      bullet.destroyed = false;
    }
  }
};
} // namespace sf
#endif
