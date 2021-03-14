#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  void PopulateContainer(const std::string& color, size_t number, double radius);

  const std::vector<Particle> &GetParticles() const;

  static const int kWindowSize = 800;
  const int kMargin = 108;

 private:
  /**
   * This variable is just for the purposes of demonstrating how to make a shape move
   * across a screen. Please remove it once you start working on your code.
   */
  const int bottom_side_ = kWindowSize - kMargin;
  const int left_side_ = kMargin;
  const int right_side_ = kWindowSize - kMargin;
  const int top_side_ = kMargin;
  const double max_velocity_ = 1.0;
  const double min_velocity_ = -1.0;

  std::vector<Particle> particles_;

  void CalculateCollisionWithWall(Particle& particle) const;

  void CalculateCollisionWithParticle();

  vec2 ChangeVelocity(Particle& particle, Particle& other);

  vec2 GiveRandomPosition();
  vec2 GiveRandomVelocity();

};

}  // namespace idealgas
