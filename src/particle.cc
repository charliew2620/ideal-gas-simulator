#include <gas_container.h>
#include <particle.h>

//to do: adjustments from week 1, histogram, adjust tests for week2,
//if time: speed up(use multiplier?), or json(find library), or equation overlay: v=root(2rt/m)?

namespace idealgas {

Particle::Particle(const vec2& position, const vec2& velocity,
                   const std::string& color, const double radius, const double mass) {
  position_ = position;
  velocity_ = velocity;
  color_ = color;
  radius_ = radius;
  mass_ = mass;
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

void Particle::SetNewVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
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

// week 2
const double Particle::GetMass() const {
  return mass_;
}
}  // namespace idealgas