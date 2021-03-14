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
  CalculateCollisionWithParticle();
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
void GasContainer::CalculateCollisionWithParticle() {
  for (size_t i = 0; i < particles_.size(); i++) {
    for (size_t j = 0; j < particles_.size(); j++) {
      if (particles_[i].canCollideWithParticle(particles_[j])) {
        vec2 particle_velocity = ChangeVelocity(particles_[i], particles_[j]);
        vec2 other_velocity = ChangeVelocity(particles_[j], particles_[i]);
        particles_[i].SetNewVelocity(particle_velocity);
        particles_[j].SetNewVelocity(other_velocity);
      }
    }
  }
}

vec2 GasContainer::ChangeVelocity(Particle& particle, Particle& other) {
  vec2 velocity_difference = particle.GetVelocity() - other.GetVelocity();
  vec2 position_difference = particle.GetPosition() - other.GetPosition();
  float length = glm::length(position_difference);
  return particle.GetVelocity() - (((velocity_difference) * (position_difference))
  / pow(length, 2) * position_difference);
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
  //https://stackoverflow.com/questions/10776073/random-double-between-min-and-max
  double x_velocity = (max_velocity_ - min_velocity_) *
                          ( (double)rand() / (double)RAND_MAX ) + min_velocity_;
  double y_velocity = sqrt(pow(max_velocity_, 2)
                           - pow(x_velocity, 2));
  return vec2(x_velocity, y_velocity);
}

}  // namespace idealgas
