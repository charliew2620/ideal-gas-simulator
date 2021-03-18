#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
  const int kWindowSize = 800;
  const int kMargin = 108;

 public:
  /**
   * Sets window size.
   */
  IdealGasApp();

  /**
   * Calls PopulateContainer() to populate container with particles.
   */
  void setup() override;

  /**
   * Draws the background of the window.
   */
  void draw() override;

  /**
   * Calls AdvanceOneFrame() method and updates particles' positions.
   */
  void update() override;

 private:
  GasContainer container_;
  const cinder::ColorT<float> kBackgroundColor = "black";
  const std::string kNormalParticleColor = "green";
  const static size_t kNormalNumber = 30;
  constexpr const static double kNormalRadius = 10;

  // week 2 stuff
  const std::string kSmallParticleColor = "red";
  const static size_t kSmallParticleNumber = 10;
  constexpr const static double kSmallParticleRadius = 5;

  const std::string kBigParticleColor = "blue";
  const static size_t kBigParticleNumber = 10;
  constexpr const static double kBigParticleRadius = 15;



};

}  // namespace idealgas