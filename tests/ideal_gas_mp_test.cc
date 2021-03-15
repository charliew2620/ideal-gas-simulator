#include <catch2/catch.hpp>
#include <particle.h>
#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Valid Particle update with wall collision") {
  SECTION("tests valid left wall collision") {
    idealgas::Particle particle(vec2(118, 700),
                                vec2(-1.5, 0),"red", 10);
    GasContainer container;
    container.CalculateCollisionWithWall();
  }
}

TEST_CASE("Particle initialization") {
  idealgas::Particle particle(vec2(700, 700),
                              vec2(0, 1.5),"red", 10);

  SECTION("Valid particle position") {
    REQUIRE(particle.GetPosition() == vec2(700, 700));
  }

  SECTION("Valid particle velocity") {
    REQUIRE(particle.GetVelocity() == vec2(0, 1.5));
  }

  SECTION("Valid particle color") {
    REQUIRE(particle.GetColor() == "red");
  }

  SECTION("Valid particle radius") {
    REQUIRE(particle.GetRadius() == 10);
  }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
