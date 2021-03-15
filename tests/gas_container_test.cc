#include <catch2/catch.hpp>
#include <particle.h>
#include <gas_container.h>

using idealgas::GasContainer;

GasContainer container = GasContainer(692, 108, 108, 692);

TEST_CASE("Valid Particle update with wall collision") {
  SECTION("tests valid left wall collision") {
    idealgas::Particle particle(vec2(108, 650),
                                vec2(-1.5, 0),"red", 10);
    container.AdvanceOneFrame();
    particle.UpdateParticle();
    REQUIRE(particle.GetVelocity() == vec2(1.5, 0));
  }
}
