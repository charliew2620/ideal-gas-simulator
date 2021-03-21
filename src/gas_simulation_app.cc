#include "gas_simulation_app.h"

#include <gas_container.h>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(GasContainer(kWindowSize - kMargin, kMargin, kWindowSize / 3,
                              kWindowSize - kMargin)),
      small_histogram_(Histogram(kWindowSize - 700, kWindowSize - 800, kMargin,
                       kWindowSize / 3 - kMargin, kSmallParticleColor)),
      normal_histogram_(Histogram(kWindowSize - 500, kWindowSize - 600, kMargin,
                                  kWindowSize / 3 - kMargin, kNormalParticleColor)),
      big_histogram_(Histogram(kWindowSize - 300, kWindowSize - 400, kMargin,
                               kWindowSize / 3 - kMargin, kBigParticleColor))
{
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

  small_histogram_.DrawHistogram(container_.GetParticlesByMass(kSmallParticleMass));
  normal_histogram_.DrawHistogram(container_.GetParticlesByMass(kNormalParticleMass));
  big_histogram_.DrawHistogram(container_.GetParticlesByMass(kBigParticleMass));
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}
}  // namespace idealgas
