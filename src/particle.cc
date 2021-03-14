#include <gas_container.h>
#include <particle.h>
#include <gas_simulation_app.h>

#include "cinder/gl/gl.h"

namespace idealgas {

Particle::Particle(const vec2& position, const vec2& velocity, const std::string color,
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
//  if (!is_initialized_) {
//    GiveRandomPosition();
//    is_initialized_ = true;
//  }
  ci::gl::color(ci::Color(color_.c_str()));
  ci::gl::drawSolidCircle(vec2(position_), static_cast<float>(radius_));
}


bool Particle::canCollideWithParticle(const Particle& other_particle) {
  if (glm::distance(this->position_, other_particle.position_) <
      this->radius_ + other_particle.radius_) {
    return glm::dot(this->position_ - other_particle.position_,
               this->velocity_ - other_particle.velocity_) < 0;
  }
  return false;
}
void Particle::SetNewVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}

}