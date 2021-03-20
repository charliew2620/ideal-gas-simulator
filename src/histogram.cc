#include "histogram.h"
#include "particle.h"

namespace idealgas {
using glm::vec2;

Histogram::Histogram(const int bottom_wall, const int top_wall,
                     const int left_wall, const int right_wall, const std::string& color) {
  bottom_wall_ = bottom_wall;
  top_wall_ = top_wall;
  left_wall_ = left_wall;
  right_wall_ = right_wall;
  color_ = color;

  histogram_length_ = right_wall_ - left_wall_;
}

//To get mass, call the getter? and make a method or constructor
void Histogram::DrawHistogram() {
  particles_speeds_ = GetSpeedsOfParticlesList();

  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(left_wall_, top_wall_), vec2(right_wall_, bottom_wall_)));
}

void Histogram::UpdateHistogram(const std::vector<Particle> &particles) {
  particles_ = particles;
  particles_speeds_ = GetSpeedsOfParticlesList();

  max_speed_ = *max_element(particles_speeds_.begin(), particles_speeds_.end());
  min_speed_ = *min_element(particles_speeds_.begin(), particles_speeds_.end());

  double bar_range = (max_speed_ - min_speed_) / kNumberOfBars;


  for (size_t i = 0; i < particles_in_bar_.size(); i++) {
    int particle_count = 0;
    if (particles_speeds_[i] >= min_speed_ && particles_speeds_[i] < bar_range) {
      particle_count++;
    }
    particles_in_bar_[i] = particle_count;
  }

  double left_bound = left_wall_;
  double right_bound = right_wall_;

//  for (int i = 0; i < kNumberOfBars; i++) {
//    int height = bottom_wall_ + particles_in_bar_[i];
//    ci::gl::color(ci::Color(color_.c_str()));
//    ci::gl::drawSolidRect(ci::Rectf(vec2(left_wall_, bottom_wall_ + height), vec2(right_wall_ + bar_range, bottom_wall_)));
//    left_bound += bar_range;
//    right_bound += bar_range;
//
//  }
}

std::vector<double> Histogram::GetSpeedsOfParticlesList() {
  std::vector<double> particles_speeds;
  if (particles_.size() >  0) {
    for (Particle particle : particles_) {
      particles_speeds.push_back(particle.GetSpeed());
    }
  }
  return particles_speeds;
}

}
