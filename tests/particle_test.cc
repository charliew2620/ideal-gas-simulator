#include <catch2/catch.hpp>
#include <particle.h>
#include <gas_container.h>

using idealgas::GasContainer;

GasContainer container = GasContainer(692, 108, 108, 692);

//TEST_CASE("Valid Particle update with wall collision") {
//  SECTION("tests valid left wall collision") {
//    idealgas::Particle particle(vec2(108, 650),
//                                vec2(-1.5, 0),"red", 10);
//    container.AdvanceOneFrame();
//    particle.UpdateParticle();
//    REQUIRE(particle.GetVelocity() == vec2(1.5, 0));
//  }
//}

TEST_CASE("Particle initialization and getters") {
  idealgas::Particle particle(vec2(650, 650), vec2(0, 1.5), "red", 10);

  SECTION("Valid particle position") {
    REQUIRE(particle.GetPosition() == vec2(650, 650));
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

  TEST_CASE("Testing velocity methods for particle") {
  idealgas::Particle particle(vec2(650, 650), vec2(1.5, 1.5), "red", 10);
  SECTION("Negating x velocity") {
    particle.NegateXVelocity();
    REQUIRE(particle.GetVelocity() == vec2(-1.5, 1.5));
  }

  SECTION("Negating y velocity") {
    particle.NegateYVelocity();
    REQUIRE(particle.GetVelocity() == vec2(1.5, -1.5));
  }

  SECTION("Velocity stays the same and position changes") {
    particle.UpdateParticle();
    REQUIRE(particle.GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(particle.GetPosition() == vec2(651.5, 651.5));
  }

  SECTION("Setting a different velocity") {
    particle.SetNewVelocity(vec2(-0.5, 2));
    REQUIRE(particle.GetVelocity() == vec2(-0.5, 2));
  }
}

  TEST_CASE("Testing particle collision boolean method") {
    idealgas::Particle particle(vec2(650, 650),
                                vec2(1.5, 0),"red", 10);

    SECTION("Outside collision distance") {
    idealgas::Particle other(vec2(600, 650),
                                vec2(1.5, 0),"red", 10);
    REQUIRE(!particle.CanCollideWithParticle(particle, other));
  }
  SECTION("In collision distance but velocities aren't opposite") {
    idealgas::Particle other(vec2(645, 650),
                             vec2(1.5, 1.5),"red", 10);
    REQUIRE(!particle.CanCollideWithParticle(particle, other));
  }
  SECTION("Is in collision distance with opposite velocities") {
    idealgas::Particle other(vec2(669, 651),
                             vec2(-1.5, 0),"red", 10);
    REQUIRE(particle.CanCollideWithParticle(particle, other));
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
