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
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Populates container with particles.
   *
   * @param color set to particle.
   * @param number of particles to populate container.
   * @param radius set to particle.
   */
  void PopulateContainer(const std::string& color, size_t number, double radius);

  static const int kWindowSize = 800;
  const int kMargin = 108;

 private:
  const int bottom_wall_ = kWindowSize - kMargin;
  const int top_wall_ = kMargin;
  const int left_wall_ = kMargin;
  const int right_wall_ = kWindowSize - kMargin;
  const double max_velocity_ = 1.5;
  const double min_velocity_ = -1.5;

  std::vector<Particle> particles_;

  /**
   * Changes particle's velocity when hitting a wall.
   *
   * @param particle passed to change velocity if necessary.
   */
  void CalculateCollisionWithWall(Particle& particle) const;

  /**
   *Changes particle's velocity if it hits another particle.
   */
  void CalculateCollisionWithParticle();

  /**
   * Returns the new velocity of the particle after colliding with
   * another particle.
   *
   * @param particle One of the particles in collision passed whose velocity
   * will be changed.
   * @param other Other particle part of collision.
   * @return the new velocity of the particle parameter.
   */
  vec2 ChangeVelocity(Particle& particle, Particle& other);

  /**
   * Spawns particle in a random position in the container.
   *
   * @return a random position within container.
   */
  vec2 GiveRandomPosition();

  /**
   * Gives particle random velocity to start with.
   *
   * @return a random 2d velocity value.
   */
  vec2 GiveRandomVelocity();

  const std::vector<Particle> &GetParticles() const;

};

}  // namespace idealgas
