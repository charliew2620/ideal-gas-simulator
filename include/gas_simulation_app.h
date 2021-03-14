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
  IdealGasApp();

  void draw() override;
  void update() override;
  void create();

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
  GasContainer container_;

  const std::string kColor = "orange";
  const static size_t  kNumber = 10;
  constexpr const static double kRadius = 10;
};

}  // namespace idealgas