#pragma once

#include <iostream>
#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {

 public:

  const std::string particle_color = "orange";
  const float particle_radius = 10;

  Particle(const glm::vec2& position, const glm::vec2& velocity, const std::string color, const double radius);

  void Draw();
  void UpdateParticle();

  const glm::vec2 &GetPosition() const;
  const glm::vec2 &GetVelocity() const;
  const std::string &GetColor() const;
  const double &GetRadius() const;

 private:
  glm::vec2  position_;
  glm::vec2  velocity_;
  std::string color_;
  double radius_;


};
} // namespace idealgas