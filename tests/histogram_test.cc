#include <catch2/catch.hpp>
#include <histogram.h>
#include <gas_container.h>
#include <particle.h>


using namespace::idealgas;

TEST_CASE("Tests if particles are correctly in each bin") {

  std::vector<Particle> particles;

  for (size_t i = 0; i < 3; i++) {
    particles.emplace_back(Particle(vec2(650, 650),
                                    vec2(0.5), "white", 8, 12));
  }

  for (size_t i = 0; i < 5; i++) {
    particles.emplace_back(Particle(vec2(650, 650),
                                    vec2(1), "white", 8, 12));
  }

  for (size_t i = 0; i < 7; i++) {
    particles.emplace_back(Particle(vec2(650, 650),
                                    vec2(5), "white", 8, 12));
  }

  Histogram white_histogram = Histogram(200, 75, 90, 250, "white", 15, 12);
  white_histogram.UpdateHistogram(particles);
  REQUIRE(white_histogram.GetBarsList()[0] == 3);
}

TEST_CASE("Tests GetSpeedsOfParticlesList getter") {
  GasContainer container = idealgas::GasContainer(692, 108, 108, 692);
  Histogram histogram = Histogram(200, 75, 90, 250, "white", 10, 10);

  container.PopulateContainer("blue", 10, 10, 10);
  container.PopulateContainer("red", 7, 6, 5);

  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(10)).size() == 10);
  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(5)).size() == 7);
}
