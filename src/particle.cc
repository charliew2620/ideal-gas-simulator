#include <gas_container.h>
#include <particle.h>

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
}
void Particle::Draw() {
}

}