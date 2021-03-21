#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
  const int kWindowSize = 900;
  const int kMargin = 100;

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

  const std::string kNormalParticleColor = "blue";
  const static size_t kNormalNumber = 25;
  constexpr const static double kNormalRadius = 12;
  constexpr const static double kNormalParticleMass = 20;

  // week 2 stuff
  const std::string kSmallParticleColor = "white";
  const static size_t kSmallParticleNumber = 25;
  constexpr const static double kSmallParticleRadius = 8;
  constexpr const static double kSmallParticleMass = 10;

  const std::string kBigParticleColor = "orange";
  const static size_t kBigParticleNumber = 25;
  constexpr const static double kBigParticleRadius = 15;
  constexpr const static double kBigParticleMass = 30;

  Histogram small_histogram_;
  Histogram normal_histogram_;
  Histogram big_histogram_;



};

}  // namespace idealgas