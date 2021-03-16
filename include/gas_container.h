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

  GasContainer(const int bottom_wall, const int top_wall,
               const int left_wall, const int right_wall);
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

  // Unused for now, kept in case if needed for week 2
  std::vector<Particle>& GetParticles();
  const double &GetMaxMagnitudeVelocity() const;
 private:
  int bottom_wall_;
  int top_wall_;
  int left_wall_;
  int right_wall_;

  // Max and min velocities should be the same value in magnitude for same mass
  const double max_velocity_ = 2;
  const double min_velocity_ = -2;

  const int magic_number_ = 2;

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
  vec2 GiveRandomPosition(double radius);

  /**
   * Gives particle random velocity to start with.
   *
   * @return a random 2d velocity value.
   */
  vec2 GiveRandomVelocity();
};

}  // namespace idealgas
