#include "../thirdparty/googletest/include/gtest/gtest.h"
#include "../include/global.h"
#include "../include/funcs.h"
#include "../include/Ship.h"
#include "../include/Asteroids.h"

TEST(EndTestShips, Positive) {
  Ship ship(10, 10, "pl1.png", Keyboard::Left, Keyboard::Right);
  Ship ship_2(10, 20, "pl2.png", Keyboard::A, Keyboard::D);
  ship.destroyed = true;
  ship_2.destroyed = true;
  long long int people = 10000000000;
  EXPECT_EQ(true, is_it_the_end(ship, ship_2, people));
}

TEST(EndTestShips, Negative) {
  Ship ship(10, 10, "pl1.png", Keyboard::Left, Keyboard::Right);
  Ship ship_2(10, 20, "pl2.png", Keyboard::A, Keyboard::D);
  ship.destroyed = true;
  ship_2.destroyed = false;
  long long int people = 10000000000;
  EXPECT_EQ(false, is_it_the_end(ship, ship_2, people));
}

TEST(EndTestPeople, Positive) {
  Ship ship(10, 10, "pl1.png", Keyboard::Left, Keyboard::Right);
  Ship ship_2(10, 20, "pl2.png", Keyboard::A, Keyboard::D);
  long long int people = 100000;
  EXPECT_EQ(true, is_it_the_end(ship, ship_2, people));
}

TEST(EndTestPeople, Negative) {
  Ship ship(10, 10, "pl1.png", Keyboard::Left, Keyboard::Right);
  Ship ship_2(10, 20, "pl2.png", Keyboard::A, Keyboard::D);
  long long int people = 7000000000;
  EXPECT_EQ(false, is_it_the_end(ship, ship_2, people));
}

/*TEST(Intersect, Positive) {
  Ship ship(10, 10, "pl1.png", Keyboard::Left, Keyboard::Right);
  Asteroid asteroid(800, 0, "asteroid.png");
  ship.right() == 500;
  asteroid.left() == 500;
  ship.left() == 200;
  asteroid.right() == 200;
  ship.bottom() == 100;
  asteroid.top() == 100;
  ship.top() == 50;
  asteroid.bottom() == 50;

  EXPECT_EQ(true, isIntersecting(ship, asteroid));
} */
