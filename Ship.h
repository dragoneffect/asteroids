#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class Ship : public Model {
public:
  Vector2f velocity;
  int ship_health = 100;
  string ship_image;
  Keyboard::Key move_left, move_right;
  bool destroyed = false; //определяет, разрушен ли корабль или нет

  Ship(float X, float Y, string ship_image, Keyboard::Key _move_left,Keyboard::Key _move_right) : Model(ship_image) {
    model_sprite.setPosition(X, Y);
    move_left = _move_left;
    move_right = _move_right;

  }
  //вычисляем позицию
  float check_x() { return model_sprite.getPosition().x; }
};
#endif
