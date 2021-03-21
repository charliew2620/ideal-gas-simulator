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

void GasContainer::Display() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(left_wall_, top_wall_), vec2(right_wall_, bottom_wall_)));

  for (Particle& particle : particles_) {
    particle.Draw();
  }
}

void GasContainer::AdvanceOneFrame() {
  HandlePossibleParticleCollision();
  for (Particle& particle : particles_) {
    CalculateCollisionWithWall(particle);
    particle.UpdateParticle();
  }
}

void GasContainer::PopulateContainer(const std::string& color, size_t amount,
                                     double radius, double mass) {
  for (size_t particle = 0; particle < amount; particle++) {
    particles_.emplace_back(GiveRandomPosition(radius),
                            glm::vec2(GiveRandomVelocity()), color, radius, mass);
  }
}

vec2 GasContainer::GiveRandomPosition(double radius) {
  // https://stackoverflow.com/questions/10776073/random-double-between-min-and-max
  // Sets a random position within container for each particle
  return vec2((right_wall_ - left_wall_ - constant_two_ * radius) *
                      ((double)rand() / (double)RAND_MAX) +
                  left_wall_ + radius,
              (bottom_wall_ - top_wall_ - constant_two_ * radius) *
                      ((double)rand() / (double)RAND_MAX) +
                  top_wall_ + radius);
}

vec2 GasContainer::GiveRandomVelocity() {
  // Gives particles random x and y velocities that total up to the magnitude
  // of max velocity
  double x_velocity =
      (max_velocity_ - min_velocity_) * ((double)rand() / (double)RAND_MAX) +
      min_velocity_;

  double y_velocity =
      sqrt(pow(max_velocity_, constant_two_) - pow(x_velocity, constant_two_));

  // https://stackoverflow.com/questions/33060893/whats-a-simple-way-to-generate-a-random-bool-in-c
  // Randomizes making y velocity negative
  // If rand_bool is true, negates the y velocity, or leaves it as is if false
  bool rand_bool = rand() & 1;
  if (rand_bool) {
    y_velocity = -y_velocity;
  }
  return vec2(x_velocity, y_velocity);
}

void GasContainer::CalculateCollisionWithWall(Particle& particle) const {
  // Checks left wall
  if (particle.GetPosition().x <= left_wall_ + particle.GetRadius() &&
      particle.GetVelocity().x < 0) {
    particle.NegateXVelocity();
  }
  // Checks right wall
  if (particle.GetPosition().x >= right_wall_ - particle.GetRadius() &&
      particle.GetVelocity().x > 0) {
    particle.NegateXVelocity();
  }
  // Checks bottom wall
  if (particle.GetPosition().y >= bottom_wall_ - particle.GetRadius() &&
      particle.GetVelocity().y > 0) {
    particle.NegateYVelocity();
  }
  // Checks top wall
  if (particle.GetPosition().y <= top_wall_ + particle.GetRadius() &&
      particle.GetVelocity().y < 0) {
    particle.NegateYVelocity();
  }
}

void GasContainer::HandlePossibleParticleCollision() {
  // Uses double for loop to check if each particle is in collision distance
  // with another particle and changes their velocities if true
  for (size_t i = 0; i < particles_.size(); i++) {
    for (size_t j = 0; j < particles_.size(); j++) {
      if (CanCollideWithParticle(particles_[i], particles_[j])) {
        vec2 particle_velocity = ChangeVelocity(particles_[i], particles_[j]);
        vec2 other_velocity = ChangeVelocity(particles_[j], particles_[i]);
        particles_[i].SetNewVelocity(particle_velocity);
        particles_[j].SetNewVelocity(other_velocity);
      }
    }
  }
}

bool GasContainer::CanCollideWithParticle(Particle& particle, Particle& other) {
  // Checks to see if particles are in collision distance with each other.
  if (glm::distance(particle.GetPosition(), other.GetPosition()) <=
      particle.GetRadius() + other.GetRadius()) {
    // Makes sure particles won't stick together using equation from document.
    return glm::dot(particle.GetPosition() - other.GetPosition(),
                    particle.GetVelocity() - other.GetVelocity()) < 0;
  }
  return false;
}

vec2 GasContainer::ChangeVelocity(Particle& particle, Particle& other) {
  // Uses equation from document to calculate new velocities of particles.
  vec2 velocity_difference = particle.GetVelocity() - other.GetVelocity();
  vec2 position_difference = particle.GetPosition() - other.GetPosition();
  float length = glm::length(position_difference);
  float mass_value = (float) (constant_two_ * other.GetMass() / (particle.GetMass()
                                                           + other.GetMass()));
  return particle.GetVelocity() - mass_value
         * ((glm::dot(velocity_difference, position_difference)) /
          pow(length, 2) * position_difference);
}

std::vector<Particle> GasContainer::GetParticlesByMass(double mass) {
  std::vector<Particle> particles;
  for (Particle particle : particles_) {
    if (particle.GetMass() == mass) {
      particles.push_back(particle);
    }
  }
  return particles;
}

std::vector<Particle>& GasContainer::GetParticles() {
  return particles_;
}
const double& GasContainer::GetMaxMagnitudeVelocity() const {
  return max_velocity_;
}
}  // namespace idealgas