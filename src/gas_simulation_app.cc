#include "gas_simulation_app.h"

#include <gas_container.h>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(GasContainer(kWindowSize - kMargin, kMargin, kWindowSize / 3,
                              kWindowSize - kMargin)),
      small_histogram_(Histogram(kWindowSize - kWindowSize * 7 / 9,
                                 kWindowSize - kWindowSize * 11 / 12, kMargin,
                                 kWindowSize * 5 / 18, kSmallParticleColor,
                                 kSmallParticleNumber, kSmallParticleMass)),
      normal_histogram_(Histogram(kWindowSize - kWindowSize * 5 / 9,
                                  kWindowSize - kWindowSize * 25 / 36, kMargin,
                                  kWindowSize * 5 / 18, kNormalParticleColor,
                                  kNormalNumber, kNormalParticleMass)),
      big_histogram_(Histogram(kWindowSize - kWindowSize * 1 / 3,
                               kWindowSize - kWindowSize * 17 / 36, kMargin,
                               kWindowSize * 5 / 18, kBigParticleColor,
                               kBigParticleNumber, kBigParticleMass)) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::setup() {
  // add the large and small particles here probably
  // either add as parameters or call method again?
  container_.PopulateContainer(kNormalParticleColor, kNormalNumber,
                               kNormalRadius, kNormalParticleMass);
  container_.PopulateContainer(kSmallParticleColor, kSmallParticleNumber,
                               kSmallParticleRadius, kSmallParticleMass);
  container_.PopulateContainer(kBigParticleColor, kBigParticleNumber,
                               kBigParticleRadius, kBigParticleMass);
}

void IdealGasApp::draw() {
  ci::Color background_color(kBackgroundColor);
  ci::gl::clear(background_color);

  container_.Display();

  small_histogram_.DrawHistogram();
  normal_histogram_.DrawHistogram();
  big_histogram_.DrawHistogram();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();

  small_histogram_.UpdateHistogram(
      container_.GetParticlesByMass(kSmallParticleMass));
  normal_histogram_.UpdateHistogram(
      container_.GetParticlesByMass(kNormalParticleMass));
  big_histogram_.UpdateHistogram(
      container_.GetParticlesByMass(kBigParticleMass));
}
}  // namespace idealgas
