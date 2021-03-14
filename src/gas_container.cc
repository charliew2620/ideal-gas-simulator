#include "gas_container.h"
#include <particle.h>

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer() {

}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("red"));
  ci::gl::drawSolidCircle(vec2(x_position_, y_position_), 10);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_side_, top_side_), vec2(right_side_, bottom_side_)));
}

void GasContainer::AdvanceOneFrame() {
//  for (int particle = 0; particle < particles_.size(); particle++) {
//    Particle &p1 = particles_[particle];
//  }
  ++x_position_;
  ++y_position_;
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
  // Checks right wall
  if (particle.GetPosition().x >= right_side_ + particle.GetRadius() &&
      particle.GetVelocity().x > 0) {
    particle.NegateXVelocity();
  }
  // Checks top wall
  if (particle.GetPosition().y >= top_side_ + particle.GetRadius() &&
      particle.GetVelocity().y > 0) {
    particle.NegateYVelocity();
  }
  // Checks bottom wall
  if (particle.GetPosition().y <= bottom_side_ + particle.GetRadius() &&
      particle.GetVelocity().y < 0) {
    particle.NegateYVelocity();
  }
}
void GasContainer::CalculateCollisionWithParticle(Particle& particle) {
}

}  // namespace idealgas
