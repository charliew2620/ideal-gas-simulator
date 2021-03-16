#pragma once

#include <iostream>
#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {

 public:
  /**
   * Particle constructor with given characteristics.
   * @param position of the particle.
   * @param velocity of the particle.
   * @param color of the particle.
   * @param radius of the particle.
   */
  Particle(const glm::vec2& position, const glm::vec2& velocity,
           const std::string& color, const double radius);

  /**
   * Draws the particle into the container.
   */
  void Draw();

  /**
   * Updates particle with new position based on velocity.
   */
  void UpdateParticle();

  /**
   * Checks if a particle is within collision distance with another particle.
   * @param One of two passed particles.
   * @param Other particle to compare with the first particle object.
   * @return true or false if the particles collide.
   */
  bool CanCollideWithParticle(Particle& particle, Particle& other);

  /**
   * Negates d component of velocity.
   */
  void NegateXVelocity();

  /**
   * Negates Y component of velocity.
   */
  void NegateYVelocity();

  /**
   * Gives particle new velocity after colliding with another particle.
   * @param new velocity passed as parameter for particle.
   */
  void SetNewVelocity(const glm::vec2& velocity);

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