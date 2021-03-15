#include <catch2/catch.hpp>
#include <particle.h>

using glm::vec2;

idealgas::Particle particle(vec2(650, 650),
                            vec2(1.5, 1.5), "red", 10);

TEST_CASE("Particle initialization and getters") {

  SECTION("Valid particle position") {
    REQUIRE(particle.GetPosition() == vec2(650, 650));
  }

  SECTION("Valid particle velocity") {
    REQUIRE(particle.GetVelocity() == vec2(1.5, 1.5));
  }

  SECTION("Valid particle color") {
    REQUIRE(particle.GetColor() == "red");
  }

  SECTION("Valid particle radius") {
    REQUIRE(particle.GetRadius() == 10);
  }
}

  TEST_CASE("Testing particle collision boolean method") {
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

TEST_CASE("Testing velocity methods for particle") {
  SECTION("Negating x velocity") {
    particle.NegateXVelocity();
    REQUIRE(particle.GetVelocity() == vec2(-1.5, 1.5));
  }

  SECTION("Negating y velocity") {
    particle.NegateYVelocity();
    REQUIRE(particle.GetVelocity() == vec2(-1.5, -1.5));
  }

  SECTION("Velocity stays the same and position changes") {
    particle.UpdateParticle();
    REQUIRE(particle.GetVelocity() == vec2(-1.5, -1.5));
    REQUIRE(particle.GetPosition() == vec2(648.5, 648.5));
  }

  SECTION("Setting a different velocity") {
    particle.SetNewVelocity(vec2(-0.5, 2));
    REQUIRE(particle.GetVelocity() == vec2(-0.5, 2));
  }
}
