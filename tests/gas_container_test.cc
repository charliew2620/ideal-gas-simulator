#include <gas_container.h>
#include <particle.h>

#include <catch2/catch.hpp>

using idealgas::GasContainer;

GasContainer container = GasContainer(692, 108, 108, 692);

TEST_CASE("Tests the spawning of particles inside container") {
  SECTION(
      "Checks if parameter values are correct in PopulateContainer method") {
    container.GetParticles().clear();
    container.PopulateContainer("green", 15, 10);
    REQUIRE(container.GetParticles().size() == 15);
    REQUIRE(container.GetParticles().at(4).GetColor() == "green");
    REQUIRE(container.GetParticles().at(5).GetRadius() == 10);
  }
  SECTION("Checks if particle fully spawns inside container") {
    for (idealgas::Particle particle : container.GetParticles()) {
      // Checks if particles spawns FULLY inside top and left wall
      REQUIRE(particle.GetPosition().x >= 108 + 10);
      REQUIRE(particle.GetPosition().y >= 108 + 10);
      // Checks if particles spawns FULLY inside bottom and right wall
      REQUIRE(particle.GetPosition().x <= 692 - 10);
      REQUIRE(particle.GetPosition().y <= 692 - 10);
    }

    SECTION(
        "Tests if velocities of particles are within initial velocity "
        "parameters") {
      // Accounts for both max and min velocities since for loop tests magnitude
      for (idealgas::Particle particle : container.GetParticles()) {
        REQUIRE(sqrt(pow(particle.GetVelocity().x, 2) +
                     pow(particle.GetVelocity().y, 2)) <=
                container.GetMaxMagnitudeVelocity());
      }
    }
  }
}

TEST_CASE("Valid particle update with wall collision") {
  SECTION("Tests valid left wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(118, 650), vec2(-1.5, 1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(119.5, 651.5));
  }

  SECTION("Tests moving away from left wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(109, 650), vec2(1.5, 1.5), "red",
                                          10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(110.5, 651.5));
  }

  SECTION("Tests valid right wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(682, 650), vec2(1.5, 1.5), "red",
                                          10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(680.5, 651.5));
  }

  SECTION("Tests moving away from right wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(687, 650), vec2(-1.5, 1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(685.5, 651.5));
  }

  SECTION("Tests valid top wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 112), vec2(-1.5, -1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(498.5, 113.5));
  }

  SECTION("Tests moving away from top wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 112), vec2(1.5, 1.5), "red",
                                          10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(501.5, 113.5));
  }

  SECTION("Tests valid bottom wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 688), vec2(-1.5, 1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(498.5, 686.5));
  }

  SECTION("Tests moving away from bottom wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 688), vec2(1.5, -1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(501.5, 686.5));
  }

  SECTION("Tests particle colliding corner of a wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(108, 692), vec2(-1.5, 1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(109.5, 690.5));
  }

  SECTION("Tests particle moving away from corner") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(108, 692), vec2(1.5, -1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(109.5, 690.5));
  }
}

TEST_CASE("Tests particle collision") {
  SECTION("Valid collision between two particles with X velocity only") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(520, 500), vec2(-1.5, 0), "red",
                                          10);
    container.GetParticles().emplace_back(vec2(500, 500), vec2(1.5, 0), "red",
                                          10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 0));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(-1.5, 0));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(521.5, 500));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(498.5, 500));
  }

  SECTION(
      "Two particles in collision distance but moving away in X component "
      "only") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(520, 500), vec2(1.5, 0), "red",
                                          10);
    container.GetParticles().emplace_back(vec2(500, 500), vec2(-1.5, 0), "red",
                                          10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 0));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(-1.5, 0));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(521.5, 500));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(498.5, 500));
  }

  SECTION("Valid collision between two particles with Y velocity only") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 500), vec2(0, 1.5), "red",
                                          10);
    container.GetParticles().emplace_back(vec2(500, 520), vec2(0, -1.5), "red",
                                          10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(0, -1.5));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(0, 1.5));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(500, 498.5));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(500, 521.5));
  }

  SECTION(
      "Two particles in collision distance but moving away in Y component "
      "only") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 500), vec2(0, -1.5), "red",
                                          10);
    container.GetParticles().emplace_back(vec2(500, 520), vec2(0, 1.5), "red",
                                          10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(0, -1.5));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(0, 1.5));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(500, 498.5));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(500, 521.5));
  }

  SECTION(
      "Valid collision between two particles with both velocity components") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(510, 500), vec2(-1.5, 1.5),
                                          "red", 10);
    container.GetParticles().emplace_back(vec2(500, 510), vec2(1.5, -1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(-1.5, 1.5));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(511.5, 498.5));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(498.5, 511.5));
  }

  SECTION(
      "Two particles in collision distance but moving away with both velocity "
      "components") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(510, 500), vec2(1.5, -1.5),
                                          "red", 10);
    container.GetParticles().emplace_back(vec2(500, 510), vec2(-1.5, 1.5),
                                          "red", 10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(-1.5, 1.5));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(511.5, 498.5));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(498.5, 511.5));
  }

  SECTION("Tests valid collision with three particles") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(510, 510), vec2(-1.5, -1.5),
                                          "red", 10);
    container.GetParticles().emplace_back(vec2(500, 500), vec2(1.5, 1.5), "red",
                                          10);
    container.GetParticles().emplace_back(vec2(490, 490), vec2(2, 2), "red",
                                          10);
    container.AdvanceOneFrame();
    // Checks new velocity
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(1).GetVelocity() == vec2(2, 2));
    REQUIRE(container.GetParticles().at(2).GetVelocity() == vec2(-1.5, -1.5));
    // Checks new position
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(511.5, 511.5));
    REQUIRE(container.GetParticles().at(1).GetPosition() == vec2(502, 502));
    REQUIRE(container.GetParticles().at(2).GetPosition() == vec2(488.5, 488.5));
  }
}

TEST_CASE(
    "Tests if kinetic energy of all particles stays approximately constant") {
  container.GetParticles().clear();
  container.PopulateContainer("green", 20, 10);
  double initial_energy_sum = 0;
  double final_energy_sum = 0;
  for (idealgas::Particle particle : container.GetParticles()) {
    // Currently does not include mass as all particles' masses are the same for
    // week1
    // Will be a factor in week 2 and changed to include it
    initial_energy_sum += 0.5 * sqrt(pow(particle.GetVelocity().x, 2) +
                                     pow(particle.GetVelocity().y, 2));
  }
  // Lets particles move around in container for chosen number of frames
  for (int i = 0; i < 20; i++) {
    container.AdvanceOneFrame();
  }

  for (idealgas::Particle particle : container.GetParticles()) {
    // Currently does not include mass as all particles' masses are the same for
    // week1
    // Will be a factor in week 2 and changed to include it
    final_energy_sum += 0.5 * sqrt(pow(particle.GetVelocity().x, 2) +
                                   pow(particle.GetVelocity().y, 2));
  }
  // https://stackoverflow.com/questions/6718343/how-to-use-floating-point-tolerances-in-the-catch-framework
  REQUIRE(initial_energy_sum == Approx(final_energy_sum).epsilon(1));
}