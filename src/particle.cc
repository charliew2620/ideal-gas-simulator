#include <gas_container.h>
#include <particle.h>

namespace idealgas {

Particle::Particle(const vec2& position, const vec2& velocity, const std::string& color,
                   const double radius) {
  position_ = position;
  velocity_ = velocity;
  color_ = color;
  radius_ = radius;
}

const glm::vec2& Particle::GetPosition() const {
  return position_;
}

const glm::vec2& Particle::GetVelocity() const {
  return velocity_;
}

const std::string& Particle::GetColor() const {
  return color_;
}

const double& Particle::GetRadius() const {
  return radius_;
}

void Particle::UpdateParticle() {
  position_ += velocity_;
}

void Particle::NegateXVelocity() {
  velocity_.x = -velocity_.x;
}

void Particle::NegateYVelocity() {
  velocity_.y = -velocity_.y;
}

void Particle::Draw() {
  ci::gl::color(ci::Color(color_.c_str()));
  ci::gl::drawSolidCircle(vec2(position_), static_cast<float>(radius_));
}


bool Particle::CanCollideWithParticle(Particle& particle, Particle& other) {
  // Checks to see if particles are in collision distance with each other.
  if (glm::distance(particle.position_, other.position_) <=
      particle.radius_ + other.radius_) {
    // Makes sure particles won't stick together using equation from document.
    return glm::dot(particle.position_ - other.position_,
                    particle.velocity_ - other.velocity_) < 0;
  }
  return false;
}
void Particle::SetNewVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}
}