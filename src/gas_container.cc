#include "gas_container.h"
#include <particle.h>
#include <random>

namespace idealgas {
using glm::vec2;

GasContainer::GasContainer(const int bottom_wall, const int top_wall,
                           const int left_wall, const int right_wall) {
  bottom_wall_ = bottom_wall;
  top_wall_ = top_wall;
  left_wall_ = left_wall;
  right_wall_ = right_wall;
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(left_wall_, top_wall_),
                                    vec2(right_wall_, bottom_wall_)));

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

void GasContainer::PopulateContainer(const std::string& color, size_t amount,
                                     double radius) {
  for (size_t particle = 0; particle < amount; particle++) {
    particles_.emplace_back(GiveRandomPosition(),
                            glm::vec2(GiveRandomVelocity()), color, radius);
  }
}

vec2 GasContainer::GiveRandomPosition() {
  //Sets a random position within container for each particle
  return vec2(rand() % (right_wall_ - left_wall_) + left_wall_,
              rand() % (bottom_wall_ - top_wall_) + top_wall_);
}

vec2 GasContainer::GiveRandomVelocity() {
  //https://stackoverflow.com/questions/10776073/random-double-between-min-and-max
  // Gives particles random x and y velocities that total up to the magnitude
  // of max velocity
  double x_velocity = (max_velocity_ - min_velocity_) *
                          ( (double)rand() / (double)RAND_MAX ) + min_velocity_;
  double y_velocity = sqrt(pow(max_velocity_, 2)
                           - pow(x_velocity, 2));
  //https://stackoverflow.com/questions/33060893/whats-a-simple-way-to-generate-a-random-bool-in-c
  //Randomizes making y velocity negative
  bool rand_bool = rand() & 1;
  if (rand_bool) {
    y_velocity = -y_velocity;
  }
  return vec2(x_velocity, y_velocity);
}

void GasContainer::CalculateCollisionWithWall(Particle& particle) const {
  // Checks left wall
  if (particle.GetPosition().x <= left_wall_ + particle.GetRadius()
      && particle.GetVelocity().x < 0) {
    particle.NegateXVelocity();
  }
  // Checks right wall
  if (particle.GetPosition().x >= right_wall_ - particle.GetRadius()
      && particle.GetVelocity().x > 0) {
    particle.NegateXVelocity();
  }
  // Checks bottom wall
  if (particle.GetPosition().y >= bottom_wall_ - particle.GetRadius()
      && particle.GetVelocity().y > 0) {
    particle.NegateYVelocity();
  }
  // Checks top wall
  if (particle.GetPosition().y <= top_wall_ + particle.GetRadius()
      && particle.GetVelocity().y < 0) {
    particle.NegateYVelocity();
  }
}

void GasContainer::CalculateCollisionWithParticle() {
  // Uses double for loop to check if each particle is in collision distance
  // with another particle and changes their velocities if true
  for (size_t i = 0; i < particles_.size(); i++) {
    for (size_t j = 0; j < particles_.size(); j++) {
      if (particles_[i].CanCollideWithParticle(particles_[i], particles_[j])) {
        vec2 particle_velocity = ChangeVelocity(particles_[i], particles_[j]);
        vec2 other_velocity = ChangeVelocity(particles_[j], particles_[i]);
        particles_[i].SetNewVelocity(particle_velocity);
        particles_[j].SetNewVelocity(other_velocity);
      }
    }
  }
}

vec2 GasContainer::ChangeVelocity(Particle& particle, Particle& other) {
  // Uses equation from document to calculate new velocities of particles.
  vec2 velocity_difference = particle.GetVelocity() - other.GetVelocity();
  vec2 position_difference = particle.GetPosition() - other.GetPosition();
  float length = glm::length(position_difference);
  return particle.GetVelocity() - ((glm::dot(velocity_difference, position_difference))
                                   / pow(length, 2) * position_difference);
}

std::vector<Particle>& GasContainer::GetParticles() {
  return particles_;
}
}  // namespace idealgas
