#include "../thirdparty/googletest/include/gtest/gtest.h"
#include "../include/global.h"
#include "../include/funcs.h"
#include "../include/Ship.h"
#include "../include/Asteroids.h"

TEST(EndTestShips, Positive) {
  long long int people = 9000000000;
  long long int survived = 10000000;
  EXPECT_EQ(true, is_it_the_end(true, true, people, survived));
}

TEST(EndTestShips, Negative) {
  long long int people = 9000000000;
  long long int survived = 10000000;
  EXPECT_EQ(false, is_it_the_end(true, false, people, survived));
}

TEST(EndTestPeople, Positive) {
  long long int people = 100000;
  long long int survived = 10000000;
  EXPECT_EQ(true, is_it_the_end(false, false, people, survived));
}

TEST(EndTestPeople, Negative) {
  long long int people = 7000000000;
  long long int survived = 10000000;
  EXPECT_EQ(false, is_it_the_end(false, false, people, survived));
}

TEST(Intersect, Positive) {
  Ship ship(100, 100, "pl1.png", Keyboard::Left, Keyboard::Right, shipBlueW);
  Asteroid asteroid(100, 100, "asteroid.png");
  EXPECT_EQ(true, isIntersecting(ship, asteroid));
}

TEST(Intersect, Negative) {
  Ship ship(600, 500, "pl1.png", Keyboard::Left, Keyboard::Right, shipBlueW);
  Asteroid asteroid(100, 100, "asteroid.png");
  EXPECT_EQ(false, isIntersecting(ship, asteroid));
}
