#include <gas_container.h>
#include <histogram.h>
#include <particle.h>

#include <catch2/catch.hpp>

using namespace ::idealgas;

TEST_CASE("Tests if particles are correctly in each bin") {
  std::vector<Particle> particles;

  for (size_t i = 0; i < 3; i++) {
    particles.emplace_back(Particle(vec2(650, 650), vec2(0.5), "white", 8, 12));
  }

  for (size_t i = 0; i < 5; i++) {
    particles.emplace_back(Particle(vec2(650, 650), vec2(1), "white", 8, 12));
  }

  for (size_t i = 0; i < 7; i++) {
    particles.emplace_back(
        Particle(vec2(650, 650), vec2(5, 0), "white", 8, 12));
  }

  Histogram histogram = Histogram(200, 75, 90, 250, "white", 15, 12);
  histogram.UpdateHistogram(particles);

  SECTION("Tests GetBarsList method") {
    // Tests if number of bars is correct
    REQUIRE(histogram.GetBarsList().size() == 10);

    int particleCount = 0;
    for (size_t i = 0; i < histogram.GetBarsList().size(); i++) {
      particleCount += histogram.GetBarsList()[i];
    }
    // Tests if number of total particles is correct
    REQUIRE(particleCount == 15);
  }

  SECTION("Tests if particles are correctly in each bin") {
    for (size_t i = 0; i < histogram.GetBarsList().size(); i++) {
      if (i == 0) {
        REQUIRE(histogram.GetBarsList()[0] == 3);

      } else if (i == 1) {
        // Checks for min speed inclusion and max speed exclusion boundary
        REQUIRE(histogram.GetBarsList()[1] == 5);

      } else if (i == 5) {
        // Checks for min speed inclusion and max speed exclusion boundary
        REQUIRE(histogram.GetBarsList()[5] == 7);

      } else {
        REQUIRE(histogram.GetBarsList()[i] == 0);
      }
    }
  }
}

TEST_CASE(
    "Tests to make sure particle speeds don't exceed max speed of histogram at "
    "any point") {
  GasContainer container = idealgas::GasContainer(692, 108, 108, 692);
  Histogram blue_histogram = Histogram(200, 75, 90, 250, "white", 25, 20);
  Histogram white_histogram = Histogram(200, 75, 90, 250, "white", 25, 12);
  Histogram orange_histogram = Histogram(200, 75, 90, 250, "white", 25, 25);

  container.PopulateContainer("blue", 25, 12, 20);
  container.PopulateContainer("red", 25, 8, 12);
  container.PopulateContainer("yellow", 25, 15, 25);

  for (size_t i = 0; i < 10; i++) {
    container.AdvanceOneFrame();
    for (size_t j = 0; j < 25; j++) {
      REQUIRE(blue_histogram.GetSpeedsOfParticlesList(
                  container.GetParticlesByMass(20))[j] <= 10);
      REQUIRE(white_histogram.GetSpeedsOfParticlesList(
                  container.GetParticlesByMass(12))[j] <= 10);
      REQUIRE(orange_histogram.GetSpeedsOfParticlesList(
                  container.GetParticlesByMass(25))[j] <= 10);
    }
  }
}

TEST_CASE(
    "Tests if histogram correctly gets all particle speeds of given mass") {
  GasContainer container = idealgas::GasContainer(692, 108, 108, 692);
  Histogram histogram = Histogram(200, 75, 90, 250, "white", 10, 10);

  container.PopulateContainer("blue", 10, 10, 10);
  container.PopulateContainer("red", 7, 6, 5);
  container.PopulateContainer("yellow", 11, 8, 8);

  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(10))
              .size() == 10);
  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(5))
              .size() == 7);
  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(8))
              .size() == 11);
}
