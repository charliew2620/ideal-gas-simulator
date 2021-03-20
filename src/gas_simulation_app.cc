#include "gas_simulation_app.h"

#include <gas_container.h>
#include "histogram.h"

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(GasContainer(kWindowSize - kMargin, kMargin, kWindowSize / 2,
                              kWindowSize - kMargin)),
      small_histogram_(kWindowSize - kMargin, kMargin / 2, kWindowSize,
                       kWindowSize / 2, kSmallParticleColor) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::setup() {
  // add the large and small particles here probably
  // either add as parameters or call method again?
  container_.PopulateContainer(kNormalParticleColor, kNormalNumber, kNormalRadius, kNormalParticleMass);
  container_.PopulateContainer(kSmallParticleColor, kSmallParticleNumber, kSmallParticleRadius, kSmallParticleMass);
  container_.PopulateContainer(kBigParticleColor, kBigParticleNumber, kBigParticleRadius, kBigParticleMass);
}

void IdealGasApp::draw() {
  ci::Color background_color(kBackgroundColor);
  ci::gl::clear(background_color);

  container_.Display();

  small_histogram_.DrawHistogram();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();

  small_histogram_.UpdateHistogram(container_.GetParticlesByMass(kSmallParticleMass));
}
}  // namespace idealgas
