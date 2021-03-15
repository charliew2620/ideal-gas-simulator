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
  const std::string kParticleColor = "green";
  const static size_t  kNumber = 30;
  constexpr const static double kRadius = 10;
};

}  // namespace idealgas