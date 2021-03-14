#include "gas_simulation_app.h"
#include <gas_container.h>

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(GasContainer::kWindowSize, GasContainer::kWindowSize);
}

void IdealGasApp::setup() {
  container_.PopulateContainer(kColor, kNumber, kRadius);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}


}  // namespace idealgas
