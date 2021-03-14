#include "gas_container.h"
#include <particle.h>
#include <random>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer() {

}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_side_, top_side_), vec2(right_side_, bottom_side_)));

  for (Particle particle : particles_) {
    particle.Draw();
  }


}

void GasContainer::AdvanceOneFrame() {
  for (Particle& particle : particles_) {
    CalculateCollisionWithWall(particle);
    particle.UpdateParticle();
  }
}
const std::vector<Particle>& GasContainer::GetParticles() const {
  return particles_;
}
void GasContainer::CalculateCollisionWithWall(Particle& particle) const {
  // Checks left wall
  if (particle.GetPosition().x <= left_side_ + particle.GetRadius() &&
      particle.GetVelocity().x < 0) {
    particle.NegateXVelocity();
  }
  // Checks bottom wall
  if (particle.GetPosition().x + particle.GetRadius() >= right_side_ &&
      particle.GetVelocity().x > 0) {
    particle.NegateXVelocity();
  }
  // Checks top wall
  if (particle.GetPosition().y >= bottom_side_ - particle.GetRadius() &&
      particle.GetVelocity().y > 0) {
    particle.NegateYVelocity();
  }
  // Checks top wall
  if (particle.GetPosition().y  - particle.GetRadius() <= top_side_ &&
      particle.GetVelocity().y < 0) {
    particle.NegateYVelocity();
  }
}
void GasContainer::CalculateCollisionWithParticle(Particle& particle) {
}
void GasContainer::PopulateContainer(const std::string& color, size_t total,
                                     double radius) {
  for (size_t particle = 0; particle < total; particle++) {
    particles_.emplace_back(GiveRandomPosition(),
                            glm::vec2(GiveRandomVelocity()), color, radius);
  }
}
vec2 GasContainer::GiveRandomPosition() {
  return vec2(rand() % 634 + 58,rand() % 634 + 58);
}
vec2 GasContainer::GiveRandomVelocity() {
  double x_velocity = (max_velocity_ - min_velocity_) *
                          ( (double)rand() / (double)RAND_MAX ) + min_velocity_;
  double y_velocity = sqrt(pow(max_velocity_, 2)
                           - pow(x_velocity, 2));
  return vec2(x_velocity, y_velocity);
}

}  // namespace idealgas
