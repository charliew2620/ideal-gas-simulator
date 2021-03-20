#include "histogram.h"
#include "particle.h"

namespace idealgas {

Histogram::Histogram(const int bottom_wall, const int top_wall,
                     const int left_wall, const int right_wall, const std::string& color) {
  bottom_wall_ = bottom_wall;
  top_wall_ = top_wall;
  left_wall_ = top_wall;
  left_wall_ = left_wall;
  right_wall_ = right_wall;
  color_ = color;
}

//To get mass, call the getter? and make a method or constructor
void Histogram::DrawHistogram() {
}

void Histogram::CreateHistogram() {
}
void Histogram::UpdateHistogram(const std::vector<Particle> &particles) {
  particles_ = particles;
}
std::vector<Particle> Histogram::GetSpeedsOfParticlesList() {
  std::vector<double> particles_speeds;
  if (particles_.size() >  0) {
    for (Particle particle : particles_) {
      particles_speeds.push_back(particle.GetSpeed());
    }
  }
}

}
