#include <catch2/catch.hpp>
#include <particle.h>
#include <gas_container.h>

using idealgas::GasContainer;

GasContainer container = GasContainer(692, 108, 108, 692);

TEST_CASE("Valid particle update with wall collision") {
  SECTION("Tests valid left wall collision") {
   container.GetParticles().emplace_back(vec2(118, 650),
                                          vec2(-1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(119.5, 651.5));
  }

  SECTION("Tests moving away from left wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(109, 650),
                                          vec2(1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(110.5, 651.5));
  }

  SECTION("Tests valid right wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(682, 650),
                                          vec2(1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(680.5, 651.5));
  }

  SECTION("Tests moving away from right wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(687, 650),
                                          vec2(-1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(685.5, 651.5));
  }

  SECTION("Tests valid top wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 112),
                                          vec2(-1.5, -1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(498.5, 113.5));
  }

  SECTION("Tests moving away from top wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 112),
                                          vec2(1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, 1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(501.5, 113.5));
  }

  SECTION("Tests valid bottom wall collision") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 688),
                                          vec2(-1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(-1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(498.5, 686.5));
  }

  SECTION("Tests moving away from bottom wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(500, 688),
                                          vec2(1.5, -1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(501.5, 686.5));
  }

  SECTION("Tests particle colliding corner of a wall") {
    container.GetParticles().clear();
    container.GetParticles().emplace_back(vec2(108, 692),
                                          vec2(-1.5, 1.5),"red", 10);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetVelocity() == vec2(1.5, -1.5));
    REQUIRE(container.GetParticles().at(0).GetPosition() == vec2(109.5, 690.5));
  }
}
