#include "../include/global.h"
#include "../include/Ship.h"
#include "../include/gui.h"

int interface(RenderWindow &window, Ship ship, Ship ship2, int count,
              long long int earthlings, long long int survived,
              float red_time) {

  Gui red(25, 532, "pl2_little.png");
  Gui blue(720, 534, "pl1_little.png");
  red.model_sprite.setRotation(45);
  blue.model_sprite.setRotation(45);

  Gui x1(45, 547, "x.png");
  Gui x2(734, 552, "x.png");

  String life, life2;

  if (ship2.ship_health == 1) {
    life = "1.png";
  } else if (ship2.ship_health == 2) {
    life = "2.png";
  } else if (ship2.ship_health == 3) {
    life = "3.png";
  } else {
    life = "0.png";
  }

  Gui life_image(70, 546, life);

  if (ship.ship_health == 1) {
    life2 = "1.png";
  } else if (ship.ship_health == 2) {
    life2 = "2.png";
  } else if (ship.ship_health == 3) {
    life2 = "3.png";
  } else {
    life2 = "0.png";
  }

  Gui life2_image(759, 551, life2);

  sf::Text text_score, text_left, text_people, text_surv, text_red;
  sf::Font font;
  std::stringstream st_score, st_left, st_surv, st_red;

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
  st_left << earthlings / 1000000000 << "b on earth";
  text_left.setString(st_left.str());
  text_left.setCharacterSize(20);
  text_left.setPosition(10, 10);
  window.draw(text_left);

  text_surv.setFont(font);
  if (survived / 1000000000 > 0) {
    st_surv << survived / 1000000000 << "b left";
  } else if (survived == 0) {
    st_surv << 0 << " left";
  } else {
    st_surv << survived / 1000000 << "m left";
  }
  text_surv.setString(st_surv.str());
  text_surv.setCharacterSize(20);
  text_surv.setPosition(690, 10);
  window.draw(text_surv);

  text_red.setFont(font);
  st_red << "ability";
  text_red.setString(st_red.str());
  text_red.setCharacterSize(20);
  text_red.setPosition(15, 575);
  if (!ship2.destroyed) {
    if (red_time == 5) {
      text_red.setColor(sf::Color::Red);
      window.draw(text_red);
    } else {
      text_red.setColor(sf::Color::White);
      window.draw(text_red);
    }
  }

  window.draw(life_image.model_sprite);
  window.draw(red.model_sprite);
  window.draw(x1.model_sprite);

  window.draw(life2_image.model_sprite);
  window.draw(blue.model_sprite);
  window.draw(x2.model_sprite);

  return 0;
}
