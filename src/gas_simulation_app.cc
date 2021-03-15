#include "gas_simulation_app.h"
#include <gas_container.h>

namespace idealgas {

IdealGasApp::IdealGasApp():container_(GasContainer(kWindowSize - kMargin, kMargin,
                                                      kMargin, kWindowSize - kMargin)) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::setup() {
  container_.PopulateContainer(kParticleColor, kNumber, kRadius);
}

void IdealGasApp::draw() {
  ci::Color background_color(kBackgroundColor);
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}
}  // namespace idealgas
