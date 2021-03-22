#include <catch2/catch.hpp>
#include <histogram.h>
#include <gas_container.h>
#include <particle.h>


using namespace::idealgas;

TEST_CASE("Tests if particles are correctly in each bin") {
  GasContainer container = idealgas::GasContainer(692, 108, 108, 692);
  Histogram histogram = Histogram(200, 75, 90, 250, "white", 10, 10);
  container.PopulateContainer("white", 10, 8, 10);
  container.PopulateContainer("white", 15, 8, 20);

  std::vector<double> particles_speeds;
  std::vector<idealgas::Particle> particles;

  particles_speeds.push_back(0.5);
  particles_speeds.push_back(0.5);
  particles_speeds.push_back(0.5);
  particles_speeds.push_back(0.5);

  particles_speeds.push_back(1.5);
  particles_speeds.push_back(1.5);

  particles_speeds.push_back(5.5);
  particles_speeds.push_back(5.5);
}

TEST_CASE("Tests GetSpeedsOfParticlesList getter") {
  GasContainer container = idealgas::GasContainer(692, 108, 108, 692);
  Histogram histogram = Histogram(200, 75, 90, 250, "white", 10, 10);

  container.PopulateContainer("blue", 10, 10, 10);
  container.PopulateContainer("red", 7, 6, 5);

  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(10)).size() == 10);
  REQUIRE(histogram.GetSpeedsOfParticlesList(container.GetParticlesByMass(5)).size() == 7);
}
