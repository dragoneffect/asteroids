#include "../include/global.h"
#include "../include/Ship.h"

int interface(RenderWindow &window, Ship ship, Ship ship2, int count,
              long long int earthlings, long long int survived) {
  Image red_image, blue_image, x_image, life_image, life2_image;
  Texture red_texture, blue_texture, x_texture, life_texture, life2_texture;
  Sprite red_sprite, blue_sprite, x1_sprite, x2_sprite, life_sprite,
      life2_sprite;

  red_image.loadFromFile("images/pl2_little.png");
  red_image.createMaskFromColor(Color(0, 0, 0));
  red_texture.loadFromImage(red_image);
  red_sprite.setTexture(red_texture);
  red_sprite.setPosition(40, 0);
  red_sprite.setRotation(45);

  blue_image.loadFromFile("images/pl1_little.png");
  blue_image.createMaskFromColor(Color(0, 0, 0));
  blue_texture.loadFromImage(blue_image);
  blue_sprite.setTexture(blue_texture);
  blue_sprite.setPosition(720, 0);
  blue_sprite.setRotation(45);

  x_image.loadFromFile("images/x.png");
  x_image.createMaskFromColor(Color(0, 0, 0));
  x_texture.loadFromImage(x_image);
  x1_sprite.setTexture(x_texture);
  x1_sprite.setPosition(60, 17);

  x2_sprite.setTexture(x_texture);
  x2_sprite.setPosition(734, 17);

  if (ship2.ship_health == 1) {
    life_image.loadFromFile("images/1.png");
  } else if (ship2.ship_health == 2) {
    life_image.loadFromFile("images/2.png");
  } else if (ship2.ship_health == 3) {
    life_image.loadFromFile("images/3.png");
  }
  else {
    life_image.loadFromFile("images/0.png");
  }
  life_image.createMaskFromColor(Color(0, 0, 0));
  life_texture.loadFromImage(life_image);
  life_sprite.setTexture(life_texture);
  life_sprite.setPosition(85, 16);

  if (ship.ship_health == 1) {
    life2_image.loadFromFile("images/1.png");
  } else if (ship.ship_health == 2) {
    life2_image.loadFromFile("images/2.png");
  } else if (ship.ship_health == 3) {
    life2_image.loadFromFile("images/3.png");
  }
  else {
    life2_image.loadFromFile("images/0.png");
  }
  life2_image.createMaskFromColor(Color(0, 0, 0));
  life2_texture.loadFromImage(life2_image);
  life2_sprite.setTexture(life2_texture);
  life2_sprite.setPosition(759, 16);

  sf::Text text_score, text_left, text_people, text_surv;
  sf::Font font;
  std::stringstream st_score, st_left, st_surv;

  if (!font.loadFromFile("font.ttf")) {
    return -1;
  }

  text_score.setFont(font);
  st_score << "score: " << count;
  text_score.setString(st_score.str());
  text_score.setCharacterSize(22);
  text_score.setPosition(350, 5);
  window.draw(text_score);

  text_left.setFont(font);
  st_left <<  earthlings / 1000000000 << "b on earth";
  text_left.setString(st_left.str());
  text_left.setCharacterSize(22);
  text_left.setPosition(10, 50);
  window.draw(text_left);

  text_surv.setFont(font);
  if (survived / 1000000000 > 0) {
    st_surv << survived / 1000000000 << "b left";
  } else if (survived == 0) {
    st_surv  << 0 << " left";
  } else {
    st_surv << survived / 100000000 << "m left";
  }
  text_surv.setString(st_surv.str());
  text_surv.setCharacterSize(22);
  text_surv.setPosition(690, 50);
  window.draw(text_surv);

  if (!ship2.destroyed) {
    window.draw(life_sprite);
    window.draw(red_sprite);
    window.draw(x1_sprite);
  }

  if (!ship.destroyed) {
    window.draw(life2_sprite);
    window.draw(blue_sprite);
    window.draw(x2_sprite);
  }

  return 0;
}
